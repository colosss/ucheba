#Часть 1 задание 4
str=input("Введите строку: ")
str=str.replace("o","*")
print('Новая строка',str+"\n")

#Часть 1 задание 10
str=input("Введите строку: ")
print('Новая строка',str[::-1]+"\n")

#Часть 2 задание 1
# k=int(input("Введите количество элементов списка: "))
# int_list=[]
# for i in range(k):
#     n=int(input("Введите целое число: "))
#     int_list.append(n)
# max=int_list[0]
# for i in int_list:
#     if i>max:
#         max=i
# print("Исходный список:",int_list)
# print("Максимальное значение списка:",max,"\n")

k=int(input("Введите количество элементов списка: "))
int_list=[]
for i in range(k):
    n=int(input("Введите целое число: "))
    int_list.append(n)
print("Исходный список:",int_list)
int_list=[x for x in int_list if x !=3]
print("Новый список:",int_list,"\n")

#Часть 2 задание 2
# k=int(input("Введите количество элементов списка: "))
# int_list=[]
# for i in range(k):
#     n=int(input("Введите целое число: "))
#     int_list.append(n)
# min=int_list[0]
# for i in int_list:
#     if i<min:
#         min=i
# print("Исходный список:",int_list)
# print("Минимальное значение списка:",min,"\n")

k=int(input("Введите количество элементов списка: "))
int_list=[]
for i in range(k):
    n=int(input("Введите целое число: "))
    int_list.append(n)
print("Исходный список:",int_list)
print("Колличество элементов равным 2:",int_list.count(2),"\n")

#Часть 3 задание 1
k=int(input("Введите количество элементов кортежа: "))
tuple_list=()
for i in range(k):
    n=input("Введите элемент: ")
    if n.isdigit():
        n=int(n)
    tuple_list+=(n,)
print("Полученный кортеж:",tuple_list)
new_t = tuple(x for x in tuple_list if x != 3)
print("Новый кортеж: ",new_t)
#Часть 3 задание 2
print('Колличество элементов равным 3: ',tuple_list.count(3))