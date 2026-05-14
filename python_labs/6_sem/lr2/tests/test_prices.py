from __future__ import annotations

import pandas as pd

from lr2.prices import TARGET_PRODUCTS, _extract_sheet_prices, build_summaries


def test_extracts_wide_fedstat_like_table() -> None:
    product = TARGET_PRODUCTS[0]
    sheet = pd.DataFrame(
        [
            ["Средние потребительские цены", None, None, None, None],
            [None, None, None, 2014, None],
            [None, None, None, "январь", "февраль"],
            [product, "Российская Федерация", "рубль", 300.0, 310.0],
        ]
    )

    result = _extract_sheet_prices(sheet, TARGET_PRODUCTS)

    assert len(result) == 2
    assert set(result["product"]) == set(TARGET_PRODUCTS)


def test_builds_average_median_and_deviations() -> None:
    product = TARGET_PRODUCTS[0]
    data = pd.DataFrame(
        {
            "product": [product, product],
            "period": [pd.Timestamp(2014, 1, 1), pd.Timestamp(2014, 2, 1)],
            "price": [300.0, 330.0],
        }
    )

    summary = build_summaries(data)[product]

    assert summary.average == 315.0
    assert summary.median == 315.0
    assert summary.dynamics["deviation_from_average"].tolist() == [-15.0, 15.0]
