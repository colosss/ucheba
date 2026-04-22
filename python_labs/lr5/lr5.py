class ch1_1:
    @staticmethod
    def func():
        my_list=list()
        k=int(input("Введите колличество элементов спика: "))
        for a in range(0, k):
            my_list.append(int(input(f"Введите {a} элемент списка: ")))
        max=my_list[0]
        def find_max(i,current_max):
            if i >=len(my_list): return current_max
            elif my_list[i]>current_max: current_max=my_list[i]
            return find_max(i+1,current_max)

        max=find_max(0,max)
        print(f"Максимальный элемент списка равен: {max}")

class ch1_2:
    @staticmethod
    def func():
        i1=int(input("Введите первое целое число: "))
        i2=int(input("Введите второе целое число: "))
        def recursion_gdc(a, b):
            if b==0: return a
            return recursion_gdc(b, a % b)

        result= recursion_gdc(i1,i2)
        print(f"Наибольший общий делитель: {result}")
            
class ch2_1:
    @staticmethod
    def func():
        i1=int(input("Введите первое целое число: "))
        i2=int(input("Введите второе целое число: "))
        simv=str(input('Введите символ ">", "<" или "=": '))
        def closure_comparison(s):
            if s==">":
                def compare(a,b):
                    return a>b
                return compare
            elif s=="<":
                def compare(a,b):
                    return a<b
                return compare
            elif s=="=":
                def compare(a,b):
                    return a==b
                return compare
            else: 
                def compare(a,b):
                    return False
                return compare
            
        print(closure_comparison(simv)(i1,i2))

class ch2_2:
    def func():
        string=str(input("Введите строку: "))
        ch=str(input("Введите символ который вы хотите удалить: "))
        def closure_del_str(s):
                def del_char(c):
                    result_str=""
                    for i in range(0, len(s)):
                        if c!=s[i]:
                            result_str+=s[i]
                    return result_str
                return del_char
        print(closure_del_str(string)(ch))


print("\n")
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