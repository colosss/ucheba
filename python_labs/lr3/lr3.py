class ch1_1:
    @staticmethod
    def func():
        val1=int(input("Введите первое число: "))
        val2=int(input("Введите второе число: "))
        result=val1**val2
        print(f'Результат возведения {val1} в степень {val2} равен {result}')
class ch1_2:
    @staticmethod
    def func():
        n=int(input("Введите число: "))
        result=(n-20)/((n**3)**0.5)
        print(f'Результат вычисления выражения равен {result}')
class ch2_1:
    @staticmethod
    def func():
        my_list=list(input("Введите список минимум из 6 элементов: ").split())
        print('Исходный список',my_list)
        print('Первый элемнт списка равен последнему?', my_list[0]==my_list[-1])
class ch2_2:
    @staticmethod
    def func():
        a=input('Введите значение переменной: ')
        print('Переменная является:', 'Number' if a.isdigit() else 'Other')

class ch3_1:
    @staticmethod
    def func():
        my_list=[1,2,3,4,9,7.4,5.3,9.7,3]
        i=1
        sum=my_list[0]
        while i < len(my_list):
            sum+=my_list[i]
            i+=1
        print('Сумма значений элементов: ', sum)

class ch3_2:
    @staticmethod
    def func():
        n=1
        z=int(input('Введите верхний предел: '))
        result=0
        for n in range(n, z+1):
            result+=(n-20)/((n**3)**0.5)
        print('Результат функции: ', result)


ch1_1.func()
ch1_2.func()
ch2_1.func()
ch2_2.func()
ch3_1.func()
ch3_2.func()

