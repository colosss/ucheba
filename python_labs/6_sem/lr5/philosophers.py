from __future__ import annotations

import random
import threading
import time
from dataclasses import dataclass
from enum import Enum
from typing import Final


class PhilosopherState(str, Enum):
    THINKING = "размышляет"
    EATING = "ест"


@dataclass(frozen=True)
class PhilosopherReport:
    name: str
    meals_eaten: int


class DiningPhilosophers:
    PHILOSOPHER_COUNT: Final[int] = 5

    def __init__(self, names: list[str] | None = None) -> None:
        self.names = names or [f"Философ {number}" for number in range(1, self.PHILOSOPHER_COUNT + 1)]
        if len(self.names) != self.PHILOSOPHER_COUNT:
            raise ValueError("За столом должно быть ровно пять философов.")

        self._forks = [threading.Lock() for _ in range(self.PHILOSOPHER_COUNT)]
        self._states = [PhilosopherState.THINKING for _ in range(self.PHILOSOPHER_COUNT)]
        self._meals = [0 for _ in range(self.PHILOSOPHER_COUNT)]
        self._state_lock = threading.Lock()

    def run(self, meals_per_philosopher: int = 3, delay: float = 0.01) -> list[PhilosopherReport]:
        if meals_per_philosopher < 1:
            raise ValueError("Количество приемов пищи должно быть положительным.")

        threads = [
            threading.Thread(target=self._live, args=(index, meals_per_philosopher, delay), daemon=True)
            for index in range(self.PHILOSOPHER_COUNT)
        ]

        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()

        return self.reports()

    def reports(self) -> list[PhilosopherReport]:
        return [PhilosopherReport(name, meals) for name, meals in zip(self.names, self._meals, strict=True)]

    def state_snapshot(self) -> list[PhilosopherState]:
        with self._state_lock:
            return list(self._states)

    def _live(self, index: int, meals_per_philosopher: int, delay: float) -> None:
        left_fork = index
        right_fork = (index + 1) % self.PHILOSOPHER_COUNT
        first_fork, second_fork = sorted((left_fork, right_fork))

        for _ in range(meals_per_philosopher):
            self._set_state(index, PhilosopherState.THINKING)
            time.sleep(random.uniform(delay / 2, delay))

            with self._forks[first_fork]:
                with self._forks[second_fork]:
                    self._set_state(index, PhilosopherState.EATING)
                    time.sleep(random.uniform(delay / 2, delay))
                    self._meals[index] += 1
                    self._set_state(index, PhilosopherState.THINKING)

    def _set_state(self, index: int, state: PhilosopherState) -> None:
        with self._state_lock:
            self._states[index] = state
