n = int(input("Введите ваш порядковый номер в журнале: "))
f = int(input("Введите номер последнего варианта: "))

if n <= f:
    variant = n
else:
    variant = n % f + 1

print("Ваш вариант:", variant)