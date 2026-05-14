from __future__ import annotations

from lr3.hospital import connect, create_schema, run_all_queries, seed_data


def main() -> None:
    with connect() as connection:
        create_schema(connection)
        seed_data(connection)
        for result in run_all_queries(connection):
            print(f"\n{result.title}")
            for row in result.rows:
                print(row)


if __name__ == "__main__":
    main()
