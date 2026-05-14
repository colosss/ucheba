from __future__ import annotations

import json
import os
import sqlite3
import time
import urllib.parse
import urllib.request
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Literal


TransactionType = Literal["income", "expense"]


@dataclass(frozen=True)
class CommandResult:
    text: str


def connect(database: str | Path = ":memory:") -> sqlite3.Connection:
    connection = sqlite3.connect(database)
    connection.row_factory = sqlite3.Row
    return connection


def create_schema(connection: sqlite3.Connection) -> None:
    connection.executescript(
        """
        PRAGMA foreign_keys = ON;

        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            telegram_id INTEGER NOT NULL UNIQUE,
            name TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS accounts (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL REFERENCES users(id),
            name TEXT NOT NULL,
            currency TEXT NOT NULL DEFAULT 'RUB',
            UNIQUE(user_id, name)
        );

        CREATE TABLE IF NOT EXISTS categories (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL REFERENCES users(id),
            name TEXT NOT NULL,
            kind TEXT NOT NULL CHECK(kind IN ('income', 'expense')),
            UNIQUE(user_id, name, kind)
        );

        CREATE TABLE IF NOT EXISTS transactions (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL REFERENCES users(id),
            account_id INTEGER NOT NULL REFERENCES accounts(id),
            category_id INTEGER NOT NULL REFERENCES categories(id),
            amount REAL NOT NULL CHECK(amount > 0),
            kind TEXT NOT NULL CHECK(kind IN ('income', 'expense')),
            happened_on TEXT NOT NULL,
            comment TEXT NOT NULL DEFAULT ''
        );

        CREATE TABLE IF NOT EXISTS budgets (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL REFERENCES users(id),
            category_id INTEGER NOT NULL REFERENCES categories(id),
            month TEXT NOT NULL,
            limit_amount REAL NOT NULL CHECK(limit_amount > 0),
            UNIQUE(user_id, category_id, month)
        );

        CREATE TABLE IF NOT EXISTS goals (
            id INTEGER PRIMARY KEY,
            user_id INTEGER NOT NULL REFERENCES users(id),
            name TEXT NOT NULL,
            target_amount REAL NOT NULL CHECK(target_amount > 0),
            saved_amount REAL NOT NULL DEFAULT 0,
            deadline TEXT NOT NULL
        );
        """
    )
    connection.commit()


class FinanceService:
    def __init__(self, connection: sqlite3.Connection) -> None:
        self.connection = connection

    def create_user(self, telegram_id: int, name: str) -> int:
        self.connection.execute(
            "INSERT OR IGNORE INTO users (telegram_id, name) VALUES (?, ?)",
            (telegram_id, name),
        )
        self.connection.commit()
        return int(self.connection.execute("SELECT id FROM users WHERE telegram_id = ?", (telegram_id,)).fetchone()["id"])

    def create_account(self, user_id: int, name: str, currency: str = "RUB") -> int:
        self.connection.execute(
            "INSERT OR IGNORE INTO accounts (user_id, name, currency) VALUES (?, ?, ?)",
            (user_id, name, currency),
        )
        self.connection.commit()
        return self._id_by_name("accounts", user_id, name)

    def create_category(self, user_id: int, name: str, kind: TransactionType) -> int:
        self.connection.execute(
            "INSERT OR IGNORE INTO categories (user_id, name, kind) VALUES (?, ?, ?)",
            (user_id, name, kind),
        )
        self.connection.commit()
        row = self.connection.execute(
            "SELECT id FROM categories WHERE user_id = ? AND name = ? AND kind = ?",
            (user_id, name, kind),
        ).fetchone()
        return int(row["id"])

    def add_transaction(
        self,
        user_id: int,
        account_name: str,
        category_name: str,
        amount: float,
        kind: TransactionType,
        happened_on: str,
        comment: str = "",
    ) -> int:
        account_id = self.create_account(user_id, account_name)
        category_id = self.create_category(user_id, category_name, kind)
        cursor = self.connection.execute(
            """
            INSERT INTO transactions
                (user_id, account_id, category_id, amount, kind, happened_on, comment)
            VALUES (?, ?, ?, ?, ?, ?, ?)
            """,
            (user_id, account_id, category_id, amount, kind, happened_on, comment),
        )
        self.connection.commit()
        return int(cursor.lastrowid)

    def set_budget(self, user_id: int, category_name: str, month: str, limit_amount: float) -> int:
        category_id = self.create_category(user_id, category_name, "expense")
        self.connection.execute(
            """
            INSERT INTO budgets (user_id, category_id, month, limit_amount)
            VALUES (?, ?, ?, ?)
            ON CONFLICT(user_id, category_id, month)
            DO UPDATE SET limit_amount = excluded.limit_amount
            """,
            (user_id, category_id, month, limit_amount),
        )
        self.connection.commit()
        row = self.connection.execute(
            "SELECT id FROM budgets WHERE user_id = ? AND category_id = ? AND month = ?",
            (user_id, category_id, month),
        ).fetchone()
        return int(row["id"])

    def set_goal(self, user_id: int, name: str, target_amount: float, saved_amount: float, deadline: str) -> int:
        cursor = self.connection.execute(
            """
            INSERT INTO goals (user_id, name, target_amount, saved_amount, deadline)
            VALUES (?, ?, ?, ?, ?)
            """,
            (user_id, name, target_amount, saved_amount, deadline),
        )
        self.connection.commit()
        return int(cursor.lastrowid)

    def get_balance_by_account(self, user_id: int) -> list[dict[str, Any]]:
        rows = self.connection.execute(
            """
            SELECT accounts.name,
                   COALESCE(SUM(CASE WHEN transactions.kind = 'income'
                        THEN transactions.amount ELSE -transactions.amount END), 0) AS balance
            FROM accounts
            LEFT JOIN transactions ON transactions.account_id = accounts.id
            WHERE accounts.user_id = ?
            GROUP BY accounts.id
            ORDER BY accounts.name
            """,
            (user_id,),
        ).fetchall()
        return _rows_to_dicts(rows)

    def get_monthly_summary(self, user_id: int, month: str) -> dict[str, float]:
        row = self.connection.execute(
            """
            SELECT
                COALESCE(SUM(CASE WHEN kind = 'income' THEN amount ELSE 0 END), 0) AS income,
                COALESCE(SUM(CASE WHEN kind = 'expense' THEN amount ELSE 0 END), 0) AS expense
            FROM transactions
            WHERE user_id = ? AND substr(happened_on, 1, 7) = ?
            """,
            (user_id, month),
        ).fetchone()
        income = float(row["income"])
        expense = float(row["expense"])
        return {"income": income, "expense": expense, "result": income - expense}

    def get_category_spending(self, user_id: int, month: str) -> list[dict[str, Any]]:
        rows = self.connection.execute(
            """
            SELECT categories.name, SUM(transactions.amount) AS spent
            FROM transactions
            JOIN categories ON categories.id = transactions.category_id
            WHERE transactions.user_id = ?
              AND transactions.kind = 'expense'
              AND substr(transactions.happened_on, 1, 7) = ?
            GROUP BY categories.id
            ORDER BY spent DESC
            """,
            (user_id, month),
        ).fetchall()
        return _rows_to_dicts(rows)

    def get_budget_progress(self, user_id: int, month: str) -> list[dict[str, Any]]:
        rows = self.connection.execute(
            """
            SELECT categories.name,
                   budgets.limit_amount,
                   COALESCE(SUM(transactions.amount), 0) AS spent,
                   budgets.limit_amount - COALESCE(SUM(transactions.amount), 0) AS rest
            FROM budgets
            JOIN categories ON categories.id = budgets.category_id
            LEFT JOIN transactions ON transactions.category_id = categories.id
                 AND transactions.kind = 'expense'
                 AND substr(transactions.happened_on, 1, 7) = budgets.month
            WHERE budgets.user_id = ? AND budgets.month = ?
            GROUP BY budgets.id
            ORDER BY categories.name
            """,
            (user_id, month),
        ).fetchall()
        return _rows_to_dicts(rows)

    def get_goals(self, user_id: int) -> list[dict[str, Any]]:
        rows = self.connection.execute(
            """
            SELECT name, target_amount, saved_amount,
                   ROUND(saved_amount * 100.0 / target_amount, 2) AS progress_percent,
                   deadline
            FROM goals
            WHERE user_id = ?
            ORDER BY deadline
            """,
            (user_id,),
        ).fetchall()
        return _rows_to_dicts(rows)

    def list_recent_transactions(self, user_id: int, limit: int = 5) -> list[dict[str, Any]]:
        rows = self.connection.execute(
            """
            SELECT transactions.happened_on, transactions.kind, accounts.name AS account,
                   categories.name AS category, transactions.amount, transactions.comment
            FROM transactions
            JOIN accounts ON accounts.id = transactions.account_id
            JOIN categories ON categories.id = transactions.category_id
            WHERE transactions.user_id = ?
            ORDER BY transactions.happened_on DESC, transactions.id DESC
            LIMIT ?
            """,
            (user_id, limit),
        ).fetchall()
        return _rows_to_dicts(rows)

    def _id_by_name(self, table: str, user_id: int, name: str) -> int:
        row = self.connection.execute(
            f"SELECT id FROM {table} WHERE user_id = ? AND name = ?",
            (user_id, name),
        ).fetchone()
        return int(row["id"])


def handle_command(service: FinanceService, telegram_id: int, text: str, name: str = "Пользователь") -> CommandResult:
    user_id = service.create_user(telegram_id, name)
    parts = text.strip().split()
    if not parts:
        return CommandResult(help_text())

    command = parts[0].lower()
    try:
        if command == "/start":
            service.create_account(user_id, "Основной")
            return CommandResult("Финансовый бот готов. Используйте /help.")
        if command == "/help":
            return CommandResult(help_text())
        if command == "/account" and len(parts) >= 2:
            service.create_account(user_id, parts[1])
            return CommandResult(f"Счет '{parts[1]}' создан.")
        if command == "/income" and len(parts) >= 4:
            service.add_transaction(user_id, parts[1], parts[2], float(parts[3]), "income", _today())
            return CommandResult("Доход добавлен.")
        if command == "/expense" and len(parts) >= 4:
            service.add_transaction(user_id, parts[1], parts[2], float(parts[3]), "expense", _today())
            return CommandResult("Расход добавлен.")
        if command == "/summary":
            month = parts[1] if len(parts) > 1 else _today()[:7]
            summary = service.get_monthly_summary(user_id, month)
            return CommandResult(
                f"{month}: доход {summary['income']:.2f}, расход {summary['expense']:.2f}, итог {summary['result']:.2f}"
            )
        if command == "/balance":
            balances = service.get_balance_by_account(user_id)
            return CommandResult("\n".join(f"{row['name']}: {row['balance']:.2f}" for row in balances) or "Счетов нет.")
        if command == "/budget" and len(parts) >= 4:
            service.set_budget(user_id, parts[1], parts[2], float(parts[3]))
            return CommandResult("Бюджет сохранен.")
        if command == "/goals":
            goals = service.get_goals(user_id)
            return CommandResult("\n".join(f"{row['name']}: {row['progress_percent']}%" for row in goals) or "Целей нет.")
        if command == "/recent":
            recent = service.list_recent_transactions(user_id)
            return CommandResult("\n".join(f"{row['happened_on']} {row['category']} {row['amount']:.2f}" for row in recent))
    except (ValueError, sqlite3.Error) as error:
        return CommandResult(f"Ошибка: {error}")

    return CommandResult(help_text())


def help_text() -> str:
    return (
        "/account название\n"
        "/income счет категория сумма\n"
        "/expense счет категория сумма\n"
        "/summary ГГГГ-ММ\n"
        "/balance\n"
        "/budget категория ГГГГ-ММ лимит\n"
        "/goals\n"
        "/recent"
    )


def run_bot(token: str, database: str | Path = "finance.sqlite3") -> None:
    with connect(database) as connection:
        create_schema(connection)
        service = FinanceService(connection)
        offset = 0
        while True:
            updates = _telegram_request(token, "getUpdates", {"timeout": 20, "offset": offset})
            for update in updates.get("result", []):
                offset = max(offset, int(update["update_id"]) + 1)
                message = update.get("message", {})
                chat_id = message.get("chat", {}).get("id")
                text = message.get("text", "")
                user = message.get("from", {})
                if chat_id is None or not text:
                    continue
                result = handle_command(service, int(user.get("id", chat_id)), text, user.get("first_name", "Пользователь"))
                _telegram_request(token, "sendMessage", {"chat_id": chat_id, "text": result.text})
            time.sleep(0.2)


def _telegram_request(token: str, method: str, payload: dict[str, Any]) -> dict[str, Any]:
    url = f"https://api.telegram.org/bot{token}/{method}"
    data = urllib.parse.urlencode(payload).encode()
    request = urllib.request.Request(url, data=data, method="POST")
    with urllib.request.urlopen(request, timeout=30) as response:
        return json.loads(response.read().decode("utf-8"))


def _today() -> str:
    return time.strftime("%Y-%m-%d")


def _rows_to_dicts(rows: list[sqlite3.Row]) -> list[dict[str, Any]]:
    return [dict(row) for row in rows]


def main() -> None:
    token = os.getenv("TELEGRAM_BOT_TOKEN")
    if token is None:
        print("Укажите TELEGRAM_BOT_TOKEN, чтобы запустить Telegram-бота.")
        return
    run_bot(token)
