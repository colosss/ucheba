from __future__ import annotations

from datetime import datetime

from lr1.car import Car, CarState


def test_car_starts_in_stop_state(tmp_path) -> None:
    car = Car(tmp_path / "car.log")

    assert car.state == CarState.STOP
    assert not (tmp_path / "car.log").exists()


def test_car_logs_state_transitions(tmp_path) -> None:
    moment = datetime(2026, 5, 12, 10, 30, 0)
    car = Car(tmp_path / "car.log", clock=lambda: moment)

    car.move_forward()
    car.accelerate()

    assert (tmp_path / "car.log").read_text(encoding="utf-8").splitlines() == [
        "2026-05-12 10:30:00; стоп; движение вперед",
        "2026-05-12 10:30:00; движение вперед; разгон",
    ]


def test_car_does_not_log_same_state(tmp_path) -> None:
    car = Car(tmp_path / "car.log")

    car.stop()

    assert not (tmp_path / "car.log").exists()
