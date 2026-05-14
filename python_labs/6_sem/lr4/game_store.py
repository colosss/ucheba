from __future__ import annotations

from dataclasses import dataclass
from decimal import Decimal
from typing import Any

from sqlalchemy import ForeignKey, create_engine, func, select
from sqlalchemy.engine import Engine
from sqlalchemy.orm import DeclarativeBase, Mapped, Session, mapped_column, relationship


class Base(DeclarativeBase):
    pass


class Category(Base):
    __tablename__ = "categories"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(unique=True)
    games: Mapped[list[Game]] = relationship(back_populates="category")


class Publisher(Base):
    __tablename__ = "publishers"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(unique=True)
    games: Mapped[list[Game]] = relationship(back_populates="publisher")


class Game(Base):
    __tablename__ = "games"

    id: Mapped[int] = mapped_column(primary_key=True)
    title: Mapped[str] = mapped_column(unique=True)
    price: Mapped[Decimal]
    stock: Mapped[int]
    category_id: Mapped[int] = mapped_column(ForeignKey("categories.id"))
    publisher_id: Mapped[int] = mapped_column(ForeignKey("publishers.id"))

    category: Mapped[Category] = relationship(back_populates="games")
    publisher: Mapped[Publisher] = relationship(back_populates="games")
    order_items: Mapped[list[OrderItem]] = relationship(back_populates="game")


class Customer(Base):
    __tablename__ = "customers"

    id: Mapped[int] = mapped_column(primary_key=True)
    full_name: Mapped[str]
    email: Mapped[str] = mapped_column(unique=True)
    orders: Mapped[list[Order]] = relationship(back_populates="customer")


class Order(Base):
    __tablename__ = "orders"

    id: Mapped[int] = mapped_column(primary_key=True)
    customer_id: Mapped[int] = mapped_column(ForeignKey("customers.id"))
    ordered_at: Mapped[str]
    status: Mapped[str]

    customer: Mapped[Customer] = relationship(back_populates="orders")
    items: Mapped[list[OrderItem]] = relationship(back_populates="order")


class OrderItem(Base):
    __tablename__ = "order_items"

    id: Mapped[int] = mapped_column(primary_key=True)
    order_id: Mapped[int] = mapped_column(ForeignKey("orders.id"))
    game_id: Mapped[int] = mapped_column(ForeignKey("games.id"))
    quantity: Mapped[int]
    price: Mapped[Decimal]

    order: Mapped[Order] = relationship(back_populates="items")
    game: Mapped[Game] = relationship(back_populates="order_items")


@dataclass(frozen=True)
class QueryResult:
    title: str
    rows: list[dict[str, Any]]


def create_database(url: str = "sqlite+pysqlite:///:memory:") -> Engine:
    engine = create_engine(url)
    Base.metadata.create_all(engine)
    return engine


def seed_data(session: Session) -> None:
    rpg = Category(id=1, name="RPG")
    strategy = Category(id=2, name="Стратегии")
    action = Category(id=3, name="Экшен")

    indie = Publisher(id=1, name="Indie Forge")
    pixel = Publisher(id=2, name="PixelWorks")
    north = Publisher(id=3, name="North Studio")

    games = [
        Game(id=1, title="Dragon Valley", price=Decimal("2499.00"), stock=8, category=rpg, publisher=indie),
        Game(id=2, title="Space Colony", price=Decimal("1799.00"), stock=3, category=strategy, publisher=pixel),
        Game(id=3, title="Neon Runner", price=Decimal("999.00"), stock=20, category=action, publisher=north),
        Game(id=4, title="Kingdom Planner", price=Decimal("1499.00"), stock=2, category=strategy, publisher=indie),
    ]

    customers = [
        Customer(id=1, full_name="Ирина Морозова", email="irina@example.com"),
        Customer(id=2, full_name="Артем Волков", email="artem@example.com"),
    ]

    orders = [
        Order(id=1, customer=customers[0], ordered_at="2026-05-01", status="paid"),
        Order(id=2, customer=customers[1], ordered_at="2026-05-03", status="paid"),
        Order(id=3, customer=customers[0], ordered_at="2026-05-05", status="created"),
    ]

    items = [
        OrderItem(id=1, order=orders[0], game=games[0], quantity=1, price=games[0].price),
        OrderItem(id=2, order=orders[0], game=games[2], quantity=2, price=games[2].price),
        OrderItem(id=3, order=orders[1], game=games[1], quantity=1, price=games[1].price),
        OrderItem(id=4, order=orders[2], game=games[3], quantity=1, price=games[3].price),
    ]

    session.add_all([rpg, strategy, action, indie, pixel, north, *games, *customers, *orders, *items])
    session.commit()


def get_games_by_category(session: Session, category_name: str) -> list[dict[str, Any]]:
    statement = (
        select(Game.title, Game.price, Game.stock, Publisher.name.label("publisher"))
        .join(Game.category)
        .join(Game.publisher)
        .where(Category.name == category_name)
        .order_by(Game.title)
    )
    return _mapping_rows(session.execute(statement).mappings().all())


def get_top_selling_games(session: Session, limit: int = 3) -> list[dict[str, Any]]:
    statement = (
        select(Game.title, func.sum(OrderItem.quantity).label("sold_count"))
        .join(OrderItem.game)
        .group_by(Game.id)
        .order_by(func.sum(OrderItem.quantity).desc(), Game.title)
        .limit(limit)
    )
    return _mapping_rows(session.execute(statement).mappings().all())


def get_customer_total_spending(session: Session) -> list[dict[str, Any]]:
    statement = (
        select(Customer.full_name, func.sum(OrderItem.quantity * OrderItem.price).label("total_spent"))
        .join(Customer.orders)
        .join(Order.items)
        .where(Order.status == "paid")
        .group_by(Customer.id)
        .order_by(func.sum(OrderItem.quantity * OrderItem.price).desc())
    )
    return _mapping_rows(session.execute(statement).mappings().all())


def get_low_stock_games(session: Session, threshold: int = 5) -> list[dict[str, Any]]:
    statement = select(Game.title, Game.stock).where(Game.stock <= threshold).order_by(Game.stock, Game.title)
    return _mapping_rows(session.execute(statement).mappings().all())


def get_orders_with_items(session: Session) -> list[dict[str, Any]]:
    statement = (
        select(
            Order.id.label("order_id"),
            Customer.full_name.label("customer"),
            Game.title.label("game"),
            OrderItem.quantity,
            Order.status,
        )
        .join(Order.customer)
        .join(Order.items)
        .join(OrderItem.game)
        .order_by(Order.id, Game.title)
    )
    return _mapping_rows(session.execute(statement).mappings().all())


def run_all_queries(session: Session) -> list[QueryResult]:
    return [
        QueryResult("Игры жанра Стратегии", get_games_by_category(session, "Стратегии")),
        QueryResult("Самые продаваемые игры", get_top_selling_games(session)),
        QueryResult("Суммы покупок клиентов", get_customer_total_spending(session)),
        QueryResult("Игры с малым остатком", get_low_stock_games(session)),
        QueryResult("Заказы с позициями", get_orders_with_items(session)),
    ]


def _mapping_rows(rows: list[Any]) -> list[dict[str, Any]]:
    return [dict(row) for row in rows]
