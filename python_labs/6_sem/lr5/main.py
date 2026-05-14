from __future__ import annotations

from lr5.philosophers import DiningPhilosophers


def main() -> None:
    table = DiningPhilosophers()
    for report in table.run(meals_per_philosopher=2):
        print(f"{report.name}: приемов пищи - {report.meals_eaten}")


if __name__ == "__main__":
    main()
