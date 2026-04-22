class ch1_1:
    @staticmethod
    def func():
        def str_case_result(func):
            def redact_func(*arg):
                result=func(*arg)
                temp1=result[:len(result)//2].upper()
                temp2=result[len(result)-len(result)//2:].lower()
                temp3=result[(len(result)-len(result)//2)-1:(len(result)//2)+1]
                new_str=temp1+temp3+temp2
                return new_str
            return redact_func

        @str_case_result
        def del_str(str, ch):
            new_str=''
            for a in str:
                if a.lower()!=ch.lower(): new_str+=a
            return new_str
        str=input("Введите строку: ")
        ch=input("Введите символ, который вы хотите удалить: ")
        print("Результат выполнения функции del_str(): "+del_str(str, ch))

class ch1_2:
    @staticmethod
    def func():
        def fahrenheit(func):
            def output_func(*arg):
                return (cels * (9/5))+32
            return output_func
        @fahrenheit
        def temperature_celsius(cels):
            return cels
        
        cels=float(input("Введите температуру в градусах Цельсия: "))
        fahr=temperature_celsius(cels)
        print(f"Температура в градусах Фаренгейта: {fahr}")

class ch2_1:
    @staticmethod
    def func():
        def my_pow(n, k):
            for i in range(k):
                n=n*n
                yield n
        n=int(input("Введите n: "))
        k=int(input("Введите колличество итераций: "))
        i=my_pow(n,k)
        print("Результат: ")
        for num in i:
            print(num)
            
class ch2_2:
    @staticmethod
    def func():
        def alphabet():
            for i in range(ord('a'), ord('z')+1):
                yield chr(i)
        print("Английский алфавит: ")
        ch=alphabet()
        for i in ch:
            print(i, end=" ")



ch1_1.func()
print("\n")
ch1_2.func()
print("\n")
ch2_1.func()
print("\n")
ch2_2.func()
print("\n")
ch1_1.func()
print("\n")
ch1_2.func()
print("\n")
ch2_1.func()
print("\n")
ch2_2.func()
print("\n")
