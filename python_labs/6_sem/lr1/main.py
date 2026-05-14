from __future__ import annotations

from pathlib import Path

from car import Car


def main() -> None:
    car = Car(Path(__file__).with_name("car.log"))
    car.move_forward()
    car.accelerate()
    car.turn_left()
    car.stop()
    print(f"Лог записан в {car.log_path}")


if __name__ == "__main__":
    main()
