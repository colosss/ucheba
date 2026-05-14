from __future__ import annotations

from decimal import Decimal
from collections.abc import Iterator

import pytest
from sqlalchemy.orm import Session

from lr4.game_store import (
    create_database,
    get_customer_total_spending,
    get_games_by_category,
    get_low_stock_games,
    get_orders_with_items,
    get_top_selling_games,
    seed_data,
)


@pytest.fixture()
def game_session() -> Iterator[Session]:
    engine = create_database()
    with Session(engine) as session:
        seed_data(session)
        yield session


def test_games_by_category_returns_strategy_games(game_session: Session) -> None:
    games = get_games_by_category(game_session, "Стратегии")

    assert [game["title"] for game in games] == ["Kingdom Planner", "Space Colony"]


def test_games_by_category_returns_empty_for_unknown_category(game_session: Session) -> None:
    assert get_games_by_category(game_session, "Гонки") == []


def test_top_selling_games_orders_by_quantity(game_session: Session) -> None:
    games = get_top_selling_games(game_session)

    assert games[0] == {"title": "Neon Runner", "sold_count": 2}


def test_top_selling_games_respects_limit(game_session: Session) -> None:
    assert len(get_top_selling_games(game_session, limit=1)) == 1


def test_customer_total_spending_counts_paid_orders_only(game_session: Session) -> None:
    spending = {row["full_name"]: row["total_spent"] for row in get_customer_total_spending(game_session)}

    assert spending["Ирина Морозова"] == Decimal("4497.00")
    assert spending["Артем Волков"] == Decimal("1799.00")


def test_customer_total_spending_excludes_created_orders(game_session: Session) -> None:
    total = sum(row["total_spent"] for row in get_customer_total_spending(game_session))

    assert total == Decimal("6296.00")


def test_low_stock_games_finds_threshold_matches(game_session: Session) -> None:
    games = get_low_stock_games(game_session, threshold=3)

    assert [game["title"] for game in games] == ["Kingdom Planner", "Space Colony"]


def test_low_stock_games_can_be_empty(game_session: Session) -> None:
    assert get_low_stock_games(game_session, threshold=1) == []


def test_orders_with_items_returns_all_order_lines(game_session: Session) -> None:
    rows = get_orders_with_items(game_session)

    assert len(rows) == 4
    assert rows[0]["customer"] == "Ирина Морозова"


def test_orders_with_items_includes_order_status(game_session: Session) -> None:
    statuses = {row["game"]: row["status"] for row in get_orders_with_items(game_session)}

    assert statuses["Kingdom Planner"] == "created"
