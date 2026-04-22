class ch1_1:
    @staticmethod
    def func():
        l=int(input("Введите размерность матрицы N: "))
        n_rows=[]
        n=[]
        for i in range(0,l):
            n_rows.append(1)
        for i in range(0,l):
            n.append(n_rows)
            print(f"[{n[i]}," if i==0 else (f"{n[i]}," if i!=l-1 else f"{n[i]}]"))
class ch1_2:
    @staticmethod
    def func():
        my_list=[1,2,3,4,9,7,4]
        my_list=[n**2 for n in my_list]
        print(my_list)
class ch2_1:
    @staticmethod
    def func():
        l1=list(input("Введите список 1: ").split())
        l1=[int(n) for n in l1]
        l2=list(input("Введите список 2: ").split())
        l2=[int(n) for n in l2]
        def add(l1:list, l2:list):
            total=sum(l1) + sum(l2)
            return total
        print("Сумма сложения всех элементов списков: ",add(l1,l2))
class ch2_2:
    @staticmethod
    def func():
        f=float(input("Введите температуру в градусах Фаренгейта: "))
        def fahrenheit_to_celsius(f:float):
            return((f-32)*(5/9))
        print(f"Температура {f} в градусах Фаренгейта равна {fahrenheit_to_celsius(f)} в градусах Цельсия")


ch1_1.func()
ch1_2.func()
ch2_1.func()
ch2_2.func()
