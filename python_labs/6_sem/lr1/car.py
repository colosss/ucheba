from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass, field
from datetime import datetime
from enum import Enum
from pathlib import Path


class CarState(str, Enum):
    STOP = "стоп"
    TURN_LEFT = "поворот налево"
    TURN_RIGHT = "поворот направо"
    MOVE_FORWARD = "движение вперед"
    ACCELERATE = "разгон"


@dataclass
class Car:
    log_path: Path | str
    state: CarState = CarState.STOP
    clock: Callable[[], datetime] = field(default=datetime.now, repr=False)

    def __post_init__(self) -> None:
        self.log_path = Path(self.log_path)
        self.log_path.parent.mkdir(parents=True, exist_ok=True)

    def set_state(self, new_state: CarState) -> None:
        if new_state == self.state:
            return

        previous_state = self.state
        self.state = new_state
        self._write_transition(previous_state, new_state)

    def stop(self) -> None:
        self.set_state(CarState.STOP)

    def turn_left(self) -> None:
        self.set_state(CarState.TURN_LEFT)

    def turn_right(self) -> None:
        self.set_state(CarState.TURN_RIGHT)

    def move_forward(self) -> None:
        self.set_state(CarState.MOVE_FORWARD)

    def accelerate(self) -> None:
        self.set_state(CarState.ACCELERATE)

    def _write_transition(self, previous_state: CarState, current_state: CarState) -> None:
        timestamp = self.clock().strftime("%Y-%m-%d %H:%M:%S")
        line = f"{timestamp}; {previous_state.value}; {current_state.value}\n"
        self.log_path.write_text(
            self.log_path.read_text(encoding="utf-8") + line
            if self.log_path.exists()
            else line,
            encoding="utf-8",
        )
