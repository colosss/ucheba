import random

n=0
A=[]
otr=0
count=0

def input_count():
    global n
    n=input("Введите колличество символов массива А\n")
    while (n.isnumeric()!=True):
        n=input("Неккоректный ввод, повторно введите колличество символов массива А\n")
    n=int(n)

def function():
    global n, count, A, otr
    rand_count=0
    for i in range(0, n):
        rand_count=random.randint(-((n//2)-1), n//2)
        A+=[rand_count]
        if rand_count<0:
            otr+=rand_count
            count+=1

def main():
    global n, count, A, count
    input_count()
    function()
    print(A)
    print(f"Сумма отрицательных элементов массива равна: {otr}\n")
    print(f"Колличество отлицательных элементов равно: {count}\n")

if __name__ == "__main__":
    main()