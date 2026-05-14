from __future__ import annotations

import asyncio
import random
from collections.abc import AsyncIterator
from time import monotonic


async def random_numbers(
    duration: float,
    *,
    interval: float = 0.1,
    minimum: int = 0,
    maximum: int = 100,
    rng: random.Random | None = None,
) -> AsyncIterator[int]:
    if duration < 0:
        raise ValueError("duration не может быть отрицательным.")
    if interval <= 0:
        raise ValueError("interval должен быть положительным.")
    if minimum > maximum:
        raise ValueError("minimum не может быть больше maximum.")

    generator = rng or random.Random()
    started_at = monotonic()
    while monotonic() - started_at < duration:
        yield generator.randint(minimum, maximum)
        await asyncio.sleep(interval)


async def collect_random_numbers(
    duration: float,
    *,
    interval: float = 0.1,
    minimum: int = 0,
    maximum: int = 100,
    rng: random.Random | None = None,
) -> list[int]:
    result: list[int] = []
    async for number in random_numbers(
        duration,
        interval=interval,
        minimum=minimum,
        maximum=maximum,
        rng=rng,
    ):
        result.append(number)
    return result
