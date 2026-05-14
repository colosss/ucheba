Лабораторная работа №6. PHP + MySQL
Тема сайта: компьютерная техника.

Файлы:
- lab6.sql — создание базы lab6_computer_shop, таблиц sections и products, начальные данные.
- db.php — параметры подключения к MySQL.
- functions.php — общие функции вывода страницы.
- index.php — вывод общей таблицы, добавление, редактирование и удаление товаров.
- matrix.php — серверный PHP-сценарий по варианту 11 из ЛР №3: поиск минимакса матрицы.
- style.css — оформление сайта.
- report_lab6.docx — отчет по лабораторной работе.

Запуск в XAMPP:
1. Запустите Apache и MySQL.
2. Скопируйте папку lab6_php_db в C:\xampp\htdocs\.
3. Откройте phpMyAdmin и импортируйте файл lab6.sql.
4. Если у MySQL задан пароль, измените $password в db.php.
5. Откройте http://localhost/lab6_php_db/index.php.
