from __future__ import annotations

import sqlite3
from dataclasses import dataclass
from pathlib import Path
from typing import Any


@dataclass(frozen=True)
class QueryResult:
    title: str
    rows: list[dict[str, Any]]


def connect(database: str | Path = ":memory:") -> sqlite3.Connection:
    connection = sqlite3.connect(database)
    connection.row_factory = sqlite3.Row
    return connection


def create_schema(connection: sqlite3.Connection) -> None:
    connection.executescript(
        """
        PRAGMA foreign_keys = ON;

        CREATE TABLE IF NOT EXISTS departments (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL UNIQUE,
            floor INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS doctors (
            id INTEGER PRIMARY KEY,
            full_name TEXT NOT NULL,
            specialty TEXT NOT NULL,
            department_id INTEGER NOT NULL REFERENCES departments(id)
        );

        CREATE TABLE IF NOT EXISTS patients (
            id INTEGER PRIMARY KEY,
            full_name TEXT NOT NULL,
            birth_year INTEGER NOT NULL,
            policy_number TEXT NOT NULL UNIQUE
        );

        CREATE TABLE IF NOT EXISTS appointments (
            id INTEGER PRIMARY KEY,
            patient_id INTEGER NOT NULL REFERENCES patients(id),
            doctor_id INTEGER NOT NULL REFERENCES doctors(id),
            appointment_date TEXT NOT NULL,
            status TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS treatments (
            id INTEGER PRIMARY KEY,
            appointment_id INTEGER NOT NULL REFERENCES appointments(id),
            diagnosis TEXT NOT NULL,
            prescription TEXT NOT NULL,
            is_active INTEGER NOT NULL DEFAULT 1
        );
        """
    )
    connection.commit()


def seed_data(connection: sqlite3.Connection) -> None:
    connection.executescript(
        """
        DELETE FROM treatments;
        DELETE FROM appointments;
        DELETE FROM patients;
        DELETE FROM doctors;
        DELETE FROM departments;

        INSERT INTO departments (id, name, floor) VALUES
            (1, 'Терапия', 2),
            (2, 'Хирургия', 3),
            (3, 'Кардиология', 4);

        INSERT INTO doctors (id, full_name, specialty, department_id) VALUES
            (1, 'Иванов Алексей Петрович', 'терапевт', 1),
            (2, 'Соколова Мария Игоревна', 'хирург', 2),
            (3, 'Ким Анна Сергеевна', 'кардиолог', 3),
            (4, 'Орлов Павел Викторович', 'терапевт', 1);

        INSERT INTO patients (id, full_name, birth_year, policy_number) VALUES
            (1, 'Петров Иван', 1988, 'POL-001'),
            (2, 'Смирнова Ольга', 1975, 'POL-002'),
            (3, 'Васильев Денис', 2001, 'POL-003');

        INSERT INTO appointments (id, patient_id, doctor_id, appointment_date, status) VALUES
            (1, 1, 1, '2026-05-10 09:00', 'завершен'),
            (2, 1, 3, '2026-05-11 12:30', 'запланирован'),
            (3, 2, 2, '2026-05-12 15:00', 'запланирован'),
            (4, 3, 4, '2026-05-12 10:30', 'завершен'),
            (5, 2, 3, '2026-05-13 11:00', 'запланирован');

        INSERT INTO treatments (id, appointment_id, diagnosis, prescription, is_active) VALUES
            (1, 1, 'ОРВИ', 'покой и теплое питье', 0),
            (2, 2, 'тахикардия', 'ЭКГ и наблюдение', 1),
            (3, 3, 'аппендицит под вопросом', 'обследование', 1),
            (4, 4, 'гастрит', 'диета', 0);
        """
    )
    connection.commit()


def get_doctors_by_department(connection: sqlite3.Connection, department_name: str) -> list[dict[str, Any]]:
    rows = connection.execute(
        """
        SELECT doctors.full_name, doctors.specialty, departments.name AS department
        FROM doctors
        JOIN departments ON departments.id = doctors.department_id
        WHERE departments.name = ?
        ORDER BY doctors.full_name
        """,
        (department_name,),
    ).fetchall()
    return _rows_to_dicts(rows)


def get_patient_appointments(connection: sqlite3.Connection, patient_name: str) -> list[dict[str, Any]]:
    rows = connection.execute(
        """
        SELECT patients.full_name AS patient, doctors.full_name AS doctor,
               departments.name AS department, appointments.appointment_date, appointments.status
        FROM appointments
        JOIN patients ON patients.id = appointments.patient_id
        JOIN doctors ON doctors.id = appointments.doctor_id
        JOIN departments ON departments.id = doctors.department_id
        WHERE patients.full_name = ?
        ORDER BY appointments.appointment_date
        """,
        (patient_name,),
    ).fetchall()
    return _rows_to_dicts(rows)


def get_department_patient_counts(connection: sqlite3.Connection) -> list[dict[str, Any]]:
    rows = connection.execute(
        """
        SELECT departments.name AS department, COUNT(DISTINCT appointments.patient_id) AS patient_count
        FROM departments
        LEFT JOIN doctors ON doctors.department_id = departments.id
        LEFT JOIN appointments ON appointments.doctor_id = doctors.id
        GROUP BY departments.id
        ORDER BY patient_count DESC, department
        """
    ).fetchall()
    return _rows_to_dicts(rows)


def get_doctor_workload(connection: sqlite3.Connection) -> list[dict[str, Any]]:
    rows = connection.execute(
        """
        SELECT doctors.full_name AS doctor, COUNT(appointments.id) AS appointment_count
        FROM doctors
        LEFT JOIN appointments ON appointments.doctor_id = doctors.id
        GROUP BY doctors.id
        ORDER BY appointment_count DESC, doctor
        """
    ).fetchall()
    return _rows_to_dicts(rows)


def get_active_treatments(connection: sqlite3.Connection) -> list[dict[str, Any]]:
    rows = connection.execute(
        """
        SELECT patients.full_name AS patient, doctors.full_name AS doctor,
               treatments.diagnosis, treatments.prescription
        FROM treatments
        JOIN appointments ON appointments.id = treatments.appointment_id
        JOIN patients ON patients.id = appointments.patient_id
        JOIN doctors ON doctors.id = appointments.doctor_id
        WHERE treatments.is_active = 1
        ORDER BY patient
        """
    ).fetchall()
    return _rows_to_dicts(rows)


def run_all_queries(connection: sqlite3.Connection) -> list[QueryResult]:
    return [
        QueryResult("Врачи отделения Терапия", get_doctors_by_department(connection, "Терапия")),
        QueryResult("Приемы пациента Петров Иван", get_patient_appointments(connection, "Петров Иван")),
        QueryResult("Количество пациентов по отделениям", get_department_patient_counts(connection)),
        QueryResult("Нагрузка врачей", get_doctor_workload(connection)),
        QueryResult("Активные лечения", get_active_treatments(connection)),
    ]


def _rows_to_dicts(rows: list[sqlite3.Row]) -> list[dict[str, Any]]:
    return [dict(row) for row in rows]
