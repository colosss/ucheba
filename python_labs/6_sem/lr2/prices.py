from __future__ import annotations

import os
import re
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path
from typing import Final

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")

import matplotlib.pyplot as plt
import pandas as pd


ProductNames = str | Iterable[str]

TARGET_PRODUCTS: Final[tuple[str, ...]] = ("Говядина (кроме бескостного мяса), кг",)


@dataclass(frozen=True)
class PriceSummary:
    product: str
    average: float
    median: float
    dynamics: pd.DataFrame


def normalize_text(value: object) -> str:
    text = str(value).replace("\xa0", " ").strip().lower()
    return re.sub(r"\s+", " ", text)


def find_product_name(value: object, products: ProductNames) -> str | None:
    normalized_value = normalize_text(value)
    for product in _normalize_products(products):
        if normalize_text(product) in normalized_value:
            return product
    return None


def load_price_data(path: Path | str, products: ProductNames = TARGET_PRODUCTS) -> pd.DataFrame:
    product_names = _normalize_products(products)
    workbook = pd.read_excel(path, sheet_name=None, header=None, engine="xlrd")
    frames = [_extract_sheet_prices(sheet, product_names) for sheet in workbook.values()]
    non_empty_frames = [frame for frame in frames if not frame.empty]
    if not non_empty_frames:
        raise ValueError("В файле не найдены строки с нужными продуктами.")

    result = pd.concat(non_empty_frames, ignore_index=True)
    if result.empty:
        raise ValueError("В файле не найдены строки с нужными продуктами.")

    result = result.drop_duplicates(subset=["product", "period"]).sort_values(["product", "period"])
    return result.reset_index(drop=True)


def build_summaries(data: pd.DataFrame) -> dict[str, PriceSummary]:
    summaries: dict[str, PriceSummary] = {}
    for product, group in data.groupby("product", sort=False):
        dynamics = group.copy()
        average = float(dynamics["price"].mean())
        median = float(dynamics["price"].median())
        dynamics["deviation_from_average"] = dynamics["price"] - average
        dynamics["deviation_from_median"] = dynamics["price"] - median
        summaries[str(product)] = PriceSummary(product=str(product), average=average, median=median, dynamics=dynamics)
    return summaries


def save_price_plot(summaries: dict[str, PriceSummary], output_path: Path | str) -> Path:
    output = Path(output_path)
    output.parent.mkdir(parents=True, exist_ok=True)

    _, ax = plt.subplots(figsize=(11, 5))
    for summary in summaries.values():
        ax.plot(summary.dynamics["period"], summary.dynamics["price"], marker="o", linewidth=1.5, label=summary.product)

    ax.set_title("Динамика средних потребительских цен")
    ax.set_xlabel("Период")
    ax.set_ylabel("Цена")
    ax.grid(True, alpha=0.3)
    ax.legend()
    plt.tight_layout()
    plt.savefig(output)
    plt.close()
    return output


def _extract_sheet_prices(sheet: pd.DataFrame, products: ProductNames) -> pd.DataFrame:
    wide_rows = _extract_wide_rows(sheet, products)
    if wide_rows:
        return pd.DataFrame(wide_rows).dropna(subset=["period", "price"])

    rows = _extract_long_rows(sheet, products)
    if rows:
        return pd.DataFrame(rows).dropna(subset=["period", "price"])

    return pd.DataFrame(columns=["product", "period", "price"])


def _extract_long_rows(sheet: pd.DataFrame, products: ProductNames) -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    for _, raw_row in sheet.iterrows():
        values = list(raw_row)
        product = next((found for value in values if (found := find_product_name(value, products))), None)
        if product is None:
            continue

        period = next((_parse_period(value) for value in values if _parse_period(value) is not None), None)
        price = _select_price_value(values)
        if period is not None and price is not None:
            rows.append({"product": product, "period": period, "price": price})
    return rows


def _extract_wide_rows(sheet: pd.DataFrame, products: ProductNames) -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    header_candidates = sheet.head(12)

    for row_index, raw_row in sheet.iterrows():
        values = list(raw_row)
        product = next((found for value in values if (found := find_product_name(value, products))), None)
        if product is None:
            continue

        for column_index, value in enumerate(values):
            price = _to_float(value)
            if price is None:
                continue

            period = _parse_period_from_headers(header_candidates, column_index)
            if period is not None:
                rows.append({"product": product, "period": period, "price": price})
    return rows


def _select_price_value(values: list[object]) -> float | None:
    numbers = [_to_float(value) for value in values]
    numbers = [number for number in numbers if number is not None and 1 <= number <= 10_000]
    return numbers[-1] if numbers else None


def _to_float(value: object) -> float | None:
    if pd.isna(value):
        return None
    if isinstance(value, int | float):
        return float(value)

    text = normalize_text(value).replace(",", ".")
    match = re.search(r"(?<!\d)(\d+(?:\.\d+)?)(?!\d)", text)
    if match is None:
        return None
    return float(match.group(1))


def _parse_period(value: object) -> pd.Timestamp | None:
    if pd.isna(value):
        return None
    if isinstance(value, pd.Timestamp):
        return value.to_period("M").to_timestamp()

    text = normalize_text(value)
    month_by_name = {
        "январ": 1,
        "феврал": 2,
        "март": 3,
        "апрел": 4,
        "май": 5,
        "июн": 6,
        "июл": 7,
        "август": 8,
        "сентябр": 9,
        "октябр": 10,
        "ноябр": 11,
        "декабр": 12,
    }

    year_match = re.search(r"(20\d{2})", text)
    if year_match is None:
        return None
    year = int(year_match.group(1))
    if not 2007 <= year <= 2015:
        return None

    numeric_month = re.search(r"(?:^|[^\d])(\d{1,2})(?:[^\d]|$)", text.replace(str(year), " "))
    if numeric_month is not None:
        month = int(numeric_month.group(1))
        if 1 <= month <= 12:
            return pd.Timestamp(year=year, month=month, day=1)

    for month_name, month in month_by_name.items():
        if month_name in text:
            return pd.Timestamp(year=year, month=month, day=1)

    return pd.Timestamp(year=year, month=1, day=1)


def _parse_period_from_headers(headers: pd.DataFrame, column_index: int) -> pd.Timestamp | None:
    for _, row in headers.iterrows():
        parsed = _parse_period(row.iloc[column_index])
        if parsed is not None:
            return parsed

    year = None
    month = None
    for _, row in headers.iterrows():
        for value in row.iloc[: column_index + 1]:
            detected_year = _parse_year(value)
            if detected_year is not None:
                year = detected_year
        month = _parse_month(row.iloc[column_index]) or month

    if year is None or month is None:
        return None
    return pd.Timestamp(year=year, month=month, day=1)


def _parse_year(value: object) -> int | None:
    if pd.isna(value):
        return None
    match = re.search(r"(20\d{2})", normalize_text(value))
    if match is None:
        return None
    year = int(match.group(1))
    return year if 2007 <= year <= 2015 else None


def _parse_month(value: object) -> int | None:
    if pd.isna(value):
        return None
    text = normalize_text(value)
    month_by_name = {
        "январ": 1,
        "феврал": 2,
        "март": 3,
        "апрел": 4,
        "май": 5,
        "июн": 6,
        "июл": 7,
        "август": 8,
        "сентябр": 9,
        "октябр": 10,
        "ноябр": 11,
        "декабр": 12,
    }
    for month_name, month in month_by_name.items():
        if month_name in text:
            return month
    return None


def _normalize_products(products: ProductNames) -> tuple[str, ...]:
    if isinstance(products, str):
        return (products,)
    return tuple(products)
