from __future__ import annotations

import pytest

from lr5.philosophers import DiningPhilosophers, PhilosopherState


def test_all_philosophers_eat_required_number_of_times() -> None:
    table = DiningPhilosophers()

    reports = table.run(meals_per_philosopher=1, delay=0.001)

    assert [report.meals_eaten for report in reports] == [1, 1, 1, 1, 1]


def test_table_requires_five_philosophers() -> None:
    with pytest.raises(ValueError):
        DiningPhilosophers(names=["Платон"])


def test_final_state_is_thinking_after_dinner() -> None:
    table = DiningPhilosophers()

    table.run(meals_per_philosopher=1, delay=0.001)

    assert table.state_snapshot() == [PhilosopherState.THINKING] * 5
