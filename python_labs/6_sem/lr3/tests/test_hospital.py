from __future__ import annotations

import sqlite3

import pytest

from lr3.hospital import (
    connect,
    create_schema,
    get_active_treatments,
    get_department_patient_counts,
    get_doctor_workload,
    get_doctors_by_department,
    get_patient_appointments,
    seed_data,
)


@pytest.fixture()
def hospital_connection() -> sqlite3.Connection:
    connection = connect()
    create_schema(connection)
    seed_data(connection)
    yield connection
    connection.close()


def test_doctors_by_department_returns_only_selected_department(hospital_connection: sqlite3.Connection) -> None:
    doctors = get_doctors_by_department(hospital_connection, "Терапия")

    assert len(doctors) == 2
    assert {doctor["department"] for doctor in doctors} == {"Терапия"}


def test_doctors_by_department_returns_empty_for_unknown_department(hospital_connection: sqlite3.Connection) -> None:
    assert get_doctors_by_department(hospital_connection, "Неврология") == []


def test_patient_appointments_are_sorted_by_date(hospital_connection: sqlite3.Connection) -> None:
    appointments = get_patient_appointments(hospital_connection, "Петров Иван")

    assert [appointment["appointment_date"] for appointment in appointments] == [
        "2026-05-10 09:00",
        "2026-05-11 12:30",
    ]


def test_patient_appointments_returns_doctor_and_department(hospital_connection: sqlite3.Connection) -> None:
    appointments = get_patient_appointments(hospital_connection, "Петров Иван")

    assert appointments[0]["doctor"] == "Иванов Алексей Петрович"
    assert appointments[1]["department"] == "Кардиология"


def test_department_patient_counts_include_all_departments(hospital_connection: sqlite3.Connection) -> None:
    counts = {row["department"]: row["patient_count"] for row in get_department_patient_counts(hospital_connection)}

    assert counts == {"Кардиология": 2, "Терапия": 2, "Хирургия": 1}


def test_department_patient_counts_reacts_to_new_appointment(hospital_connection: sqlite3.Connection) -> None:
    hospital_connection.execute(
        "INSERT INTO appointments (patient_id, doctor_id, appointment_date, status) VALUES (3, 2, '2026-05-14', 'запланирован')"
    )

    counts = {row["department"]: row["patient_count"] for row in get_department_patient_counts(hospital_connection)}

    assert counts["Хирургия"] == 2


def test_doctor_workload_orders_by_appointment_count(hospital_connection: sqlite3.Connection) -> None:
    workload = get_doctor_workload(hospital_connection)

    assert workload[0] == {"doctor": "Ким Анна Сергеевна", "appointment_count": 2}


def test_doctor_workload_counts_new_appointment(hospital_connection: sqlite3.Connection) -> None:
    hospital_connection.execute(
        "INSERT INTO appointments (patient_id, doctor_id, appointment_date, status) VALUES (2, 1, '2026-05-15', 'запланирован')"
    )

    workload = {row["doctor"]: row["appointment_count"] for row in get_doctor_workload(hospital_connection)}

    assert workload["Иванов Алексей Петрович"] == 2


def test_active_treatments_returns_only_active_rows(hospital_connection: sqlite3.Connection) -> None:
    treatments = get_active_treatments(hospital_connection)

    assert len(treatments) == 2
    assert {treatment["diagnosis"] for treatment in treatments} == {"тахикардия", "аппендицит под вопросом"}


def test_active_treatments_can_be_empty(hospital_connection: sqlite3.Connection) -> None:
    hospital_connection.execute("UPDATE treatments SET is_active = 0")

    assert get_active_treatments(hospital_connection) == []
