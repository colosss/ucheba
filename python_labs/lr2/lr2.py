class ch1_1:
    def func(self):
        l=list(input("Введите список: ").split())
        print('Новый список',l, "\n")
        mn=set(input("Введите множество: ").split())
        print('Новое множество',mn)
        mn=mn.union(l)
        print('Объединение множеств',mn)
        
class ch1_2:
    def func(self):
        str=input("Введите строку: ")
        mn=set()
        for c in str:
            mn.add(c)
        print('Множество уникальных символов строки',mn)

class ch1_3:
    def func(self):
        l=list(input("Введите список: ").split())
        print('Новый список',l)
        l2=list(set(l))
        print('Список уникальных элементов',l2)

class ch2_1:
    def func(self):
        d={}
        k=int(input("Введите количество элементов словаря: "))
        for i in range(k):
            key=input("Введите ключ: ")
            value=input("Введите значение: ")
            if value.isdigit():
                value=int(value)
            d[key]=value
        print('Исходный словарь',d)
        if d['a']==5:
            del d['a']
        print('Новый словарь',d)

class ch2_2:
    
    @staticmethod
    def func():
        d={}
        k=int(input("Введите количество элементов словаря: "))
        i=0

        # Рекурсивная функция для ввода элементов словаря
        def vvod(i, d, k):
            input_key = input("Введите ключ: ")
            input_value = int(input("Введите значение: "))
            d[input_key] = input_value
            i += 1
            if i < k:
                vvod(i, d, k)

        vvod(i, d, k)
        print('Исходный словарь',d)
        values=d.values()
        mx=max(values)
        print('Максимальное значение словаря', mx)

class ch2_3:
    @staticmethod
    def func():
        d={}
        k=int(input("Введите количество элементов словаря: "))
        i=0

        def vvod(i, d, k):
            input_key = input("Введите ключ: ")
            input_value = int(input("Введите значение: "))
            d[input_key] = input_value
            i += 1
            if i < k:
                vvod(i, d, k)
        vvod(i, d, k)
        print('Исходный словарь',d)
        values=d.values()
        if 15 in values:
            print("Значение 15 присутствует в словаре")
        else:
            print("Значение 15 отсутствует в словаре")
        

a=ch1_1()
a.func()

b=ch1_2()
b.func()

c=ch1_3()
c.func()

d=ch2_1()
d.func()


ch2_2.func()

ch2_3.func()
