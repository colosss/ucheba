from __future__ import annotations

from pathlib import Path

try:
    from lr2.prices import TARGET_PRODUCTS, build_summaries, load_price_data, save_price_plot
except ModuleNotFoundError:
    from prices import TARGET_PRODUCTS, build_summaries, load_price_data, save_price_plot


def main() -> None:
    base_dir = Path(__file__).parent
    try:
        data = load_price_data(base_dir / "data.xls")
    except ValueError as error:
        print(error)
        print(f"Проверьте, что data.xls содержит товары: {', '.join(TARGET_PRODUCTS)}.")
        return

    summaries = build_summaries(data)
    plot_path = save_price_plot(summaries, base_dir / "price_dynamics.png")

    for summary in summaries.values():
        print(f"{summary.product}: среднее={summary.average:.2f}, медиана={summary.median:.2f}")
        print(summary.dynamics.to_string(index=False))
    print(f"График сохранен в {plot_path}")


if __name__ == "__main__":
    main()
