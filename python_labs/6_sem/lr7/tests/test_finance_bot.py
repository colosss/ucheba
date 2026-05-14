from __future__ import annotations

import sqlite3

import pytest

from lr7.finance_bot import FinanceService, connect, create_schema, handle_command


@pytest.fixture()
def finance_service() -> FinanceService:
    connection = connect()
    create_schema(connection)
    service = FinanceService(connection)
    yield service
    connection.close()


def test_schema_contains_required_tables(finance_service: FinanceService) -> None:
    rows = finance_service.connection.execute(
        "SELECT name FROM sqlite_master WHERE type = 'table' ORDER BY name"
    ).fetchall()

    assert {row["name"] for row in rows} >= {"users", "accounts", "categories", "transactions", "budgets", "goals"}


def test_balance_by_account_counts_income_and_expense(finance_service: FinanceService) -> None:
    user_id = finance_service.create_user(123, "Анна")
    finance_service.add_transaction(user_id, "Карта", "Зарплата", 1000, "income", "2026-05-01")
    finance_service.add_transaction(user_id, "Карта", "Еда", 250, "expense", "2026-05-02")

    balances = finance_service.get_balance_by_account(user_id)

    assert balances == [{"name": "Карта", "balance": 750.0}]


def test_monthly_summary_and_category_spending(finance_service: FinanceService) -> None:
    user_id = finance_service.create_user(123, "Анна")
    finance_service.add_transaction(user_id, "Карта", "Зарплата", 1000, "income", "2026-05-01")
    finance_service.add_transaction(user_id, "Карта", "Еда", 250, "expense", "2026-05-02")
    finance_service.add_transaction(user_id, "Карта", "Еда", 150, "expense", "2026-05-04")

    assert finance_service.get_monthly_summary(user_id, "2026-05") == {
        "income": 1000.0,
        "expense": 400.0,
        "result": 600.0,
    }
    assert finance_service.get_category_spending(user_id, "2026-05") == [{"name": "Еда", "spent": 400.0}]


def test_budget_progress_shows_remaining_limit(finance_service: FinanceService) -> None:
    user_id = finance_service.create_user(123, "Анна")
    finance_service.set_budget(user_id, "Еда", "2026-05", 500)
    finance_service.add_transaction(user_id, "Карта", "Еда", 125, "expense", "2026-05-03")

    progress = finance_service.get_budget_progress(user_id, "2026-05")

    assert progress == [{"name": "Еда", "limit_amount": 500.0, "spent": 125.0, "rest": 375.0}]


def test_goals_and_recent_transactions(finance_service: FinanceService) -> None:
    user_id = finance_service.create_user(123, "Анна")
    finance_service.set_goal(user_id, "Ноутбук", 100_000, 25_000, "2026-12-31")
    finance_service.add_transaction(user_id, "Карта", "Еда", 125, "expense", "2026-05-03", "обед")

    assert finance_service.get_goals(user_id)[0]["progress_percent"] == 25.0
    assert finance_service.list_recent_transactions(user_id)[0]["comment"] == "обед"


def test_handle_command_adds_expense_and_returns_balance(finance_service: FinanceService) -> None:
    handle_command(finance_service, 777, "/start", "Игорь")
    handle_command(finance_service, 777, "/income Основной Зарплата 1000", "Игорь")
    handle_command(finance_service, 777, "/expense Основной Такси 300", "Игорь")

    result = handle_command(finance_service, 777, "/balance", "Игорь")

    assert "Основной: 700.00" in result.text


def test_handle_command_reports_parse_errors(finance_service: FinanceService) -> None:
    result = handle_command(finance_service, 777, "/expense Основной Такси сумма", "Игорь")

    assert result.text.startswith("Ошибка:")
