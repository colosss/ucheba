from __future__ import annotations

from sqlalchemy.orm import Session

from lr4.game_store import create_database, run_all_queries, seed_data


def main() -> None:
    engine = create_database()
    with Session(engine) as session:
        seed_data(session)
        for result in run_all_queries(session):
            print(f"\n{result.title}")
            for row in result.rows:
                print(row)


if __name__ == "__main__":
    main()
