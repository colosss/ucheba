#!/usr/bin/env python
import html
import os
import sys
from urllib.parse import parse_qs

length = int(os.environ.get("CONTENT_LENGTH", "0") or "0")
body = sys.stdin.buffer.read(length).decode("utf-8")
form = parse_qs(body, keep_blank_values=True)

print("Content-Type: text/html; charset=utf-8")
print()

names = ["Фамилия", "Имя", "Отчество", "Раздел", "Цель", "Оплата", "Тема"]
fields = ["familia", "name", "otchestvo", "device", "purpose", "pay", "theme"]

data = ["", "", "", "", "", "", ""]
i = 0

for field in fields:
    if field in form:
        values = []
        for x in form[field]:
            values.append(html.escape(x))
        data[i] = ", ".join(values)
    else:
        data[i] = "не указано"
    i = i + 1

file = open("anketa.txt", "a", encoding="utf-8")
file.write("; ".join(data) + "\n")
file.close()

print("""<!DOCTYPE html>
<html lang="ru">
<head>
<meta charset="utf-8">
<title>Ответ сервера</title>
<style>
body {
    font-family: Arial;
    background: #f2f2f2;
    margin: 0;
}
.wrapper {
    width: 900px;
    margin: 30px auto;
    background: white;
    padding: 20px;
    border: 1px solid #cccccc;
}
h1 {
    text-align: center;
}
table {
    width: 100%;
    border-collapse: collapse;
    margin-bottom: 25px;
}
td {
    border: 1px solid #777777;
    padding: 8px;
    text-align: center;
}
dt {
    font-weight: bold;
    margin-top: 10px;
}
dd {
    margin-left: 20px;
}
a {
    color: #333333;
}
</style>
</head>
<body>
<div class="wrapper">
<h1>Данные анкеты</h1>
<table>
<tr>""")

for name in names:
    print("<td>" + name + "</td>")

print("</tr><tr>")

for el in data:
    print("<td>" + el + "</td>")

print("</tr></table>")

print("<h2>Список определений</h2>")
print("<dl>")

i = 0
for name in names:
    print("<dt>" + name + "</dt>")
    print("<dd>" + data[i] + "</dd>")
    i = i + 1

print("""</dl>
<p><a href="/forma.htm">Вернуться к форме</a></p>
</div>
</body>
</html>""")
