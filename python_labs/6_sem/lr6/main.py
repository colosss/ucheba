from __future__ import annotations

import asyncio

from lr6.random_generator import random_numbers


async def main() -> None:
    async for number in random_numbers(1.0, interval=0.2, minimum=1, maximum=10):
        print(number)


if __name__ == "__main__":
    asyncio.run(main())
