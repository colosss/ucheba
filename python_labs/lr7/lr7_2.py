class Student:
    def __init__(self, fio, admission_date):
        self.fio = fio
        self.admission_date = admission_date

    def __str__(self):
        return f"{self.fio} (поступил: {self.admission_date})"


class AcademicGroup:
    def __init__(self, min_students, max_students):
        self.min_students = min_students
        self.max_students = max_students
        self.students = []

    def add_student(self, student):
        if len(self.students) >= self.max_students:
            print(f"Нельзя добавить студента: группа переполнена (максимум {self.max_students})")
            return False
        self.students.append(student)
        print(f"Добавлен студент: {student}")
        return True

    def remove_student(self, fio):
        for student in self.students[:]:
            if student.fio == fio:
                self.students.remove(student)
                print(f"Удалён студент: {student}")
                return True
        print(f"Студент с ФИО '{fio}' не найден в группе")
        return False

    def find_student(self, fio):
        found = [s for s in self.students if s.fio == fio]
        return found if found else None

    def count_students(self):
        return len(self.students)

    def __str__(self):
        if not self.students:
            return "Группа пуста."
        lines = [f"Академическая группа (мин: {self.min_students}, макс: {self.max_students}):"]
        for i, student in enumerate(self.students, 1):
            lines.append(f"{i}. {student}")
        lines.append(f"Всего студентов: {self.count_students()}")
        return "\n".join(lines)


if __name__ == "__main__":
    group = AcademicGroup(min_students=10, max_students=25)

    s1 = Student("Иванов Иван Иванович", "01.09.2023")
    s2 = Student("Петров Пётр Петрович", "01.09.2023")
    s3 = Student("Сидорова Анна Сергеевна", "01.09.2024")

    group.add_student(s1)
    group.add_student(s2)
    group.add_student(s3)

    print("\nТекущее состояние группы:")
    print(group)

    print("\nПоиск студента 'Иванов Иван Иванович':")
    found = group.find_student("Иванов Иван Иванович")
    if found:
        for s in found:
            print(s)

    group.remove_student("Петров Пётр Петрович")

    print("\nПосле удаления:")
    print(group)

    for _ in range(30):
        group.add_student(Student(f"Студент {_+4}", "01.09.2025"))

    print("\nФинальное состояние:")
    print(group)