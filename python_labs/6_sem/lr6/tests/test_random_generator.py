from __future__ import annotations

import asyncio
import random

import pytest

from lr6.random_generator import collect_random_numbers


def test_random_numbers_are_within_bounds() -> None:
    numbers = asyncio.run(
        collect_random_numbers(0.01, interval=0.001, minimum=10, maximum=12, rng=random.Random(1))
    )

    assert numbers
    assert all(10 <= number <= 12 for number in numbers)


def test_zero_duration_returns_empty_list() -> None:
    assert asyncio.run(collect_random_numbers(0, interval=0.001)) == []


def test_invalid_duration_raises_error() -> None:
    with pytest.raises(ValueError):
        asyncio.run(collect_random_numbers(-1))


def test_invalid_bounds_raise_error() -> None:
    with pytest.raises(ValueError):
        asyncio.run(collect_random_numbers(0.01, minimum=5, maximum=1))
