import time

def Logger(func):
    def output_func(*args, **kwargs):
        print("\nАргументы функции:", ", ".join(map(str, args)))
        print("Начало работы функции\n")
        start_time=time.time()
        result=func(*args, **kwargs)
        end_time=time.time()
        print(f"\nКонец выполнения функции, время выполнения = {end_time-start_time}\n")
        return result
    return output_func

    
class Data:
    def __init__(self, year, month, day):
        self.year=year
        self.month=month
        self.day=day
        print(f"Дата создана {self.year}.{self.month}.{self.day}")
    def __del__(self):
        print("Удаление даты")
    def __str__(self):
        return f"{self.year}.{self.month}.{self.day}"
    def __lt__(a, b):
        if a.year<=b.year:
            if a.month<=b.month:
                if a.day<b.day:
                    return True
                elif a.month<b.month:
                    return True
                elif a.year<b.year:
                    return True
        return False
    def __le__(a,b):
        if a.year<=b.year and a.month<=b.month and a.day<=b.day:
            return True
        return False
    def __eq__(a,b):
        if a.year==b.year and a.month == b.month and a.day==b.day:
            return True
        return False
    def __ne__(a,b):
        if a.year!=b.year or a.month != b.month or a.day != b.day:
            return True
        return False
    def __ge__(a,b):
        if a.year>=b.year and a.month >= b.month and a.day >= b.day:
            return True
        return False
    def __gt__(a,b):
        if a.year>=b.year:
            if a.month>=b.month:
                if a.day>b.day:
                    return True
                elif a.month>b.month:
                    return True
                elif a.year>b.year:
                    return True
        return False
@Logger
def func(data1, data2, data3, data4, data5):
    
    print(f"data1<data2 | {data1}<{data2}: {data1<data2}")
    print(f"data1<data3 | {data1}<{data3}: {data1<data3}")
    print(f"data1<data4 | {data1}<{data4}: {data1<data4}")
    print(f"data1<data5 | {data1}<{data5}: {data1<data5}")
    print(f"data2<data1 | {data1}<{data5}: {data2<data1}")
    print(f"data3<data1 | {data3}<{data1}: {data3<data1}")
    print(f"data4<data1 | {data4}<{data1}: {data4<data1}")
    print(f"data5<data1 | {data5}<{data1}: {data5<data1}")

    print("\n")

    print(f"data1<=data2 | {data1}<={data2}: {data1<=data2}")
    print(f"data1<=data3 | {data1}<={data3}: {data1<=data3}")
    print(f"data1<=data4 | {data1}<={data4}: {data1<=data4}")
    print(f"data1<=data5 | {data1}<={data5}: {data1<=data5}")
    print(f"data2<=data1 | {data1}<={data5}: {data2<=data1}")
    print(f"data3<=data1 | {data3}<={data1}: {data3<=data1}")
    print(f"data4<=data1 | {data4}<={data1}: {data4<=data1}")
    print(f"data5<=data1 | {data5}<={data1}: {data5<=data1}")

    print("\n")

    print(f"data1==data2 | {data1}=={data2}: {data1==data2}")
    print(f"data1==data3 | {data1}=={data3}: {data1==data3}")
    print(f"data1==data4 | {data1}=={data4}: {data1==data4}")
    print(f"data1==data5 | {data1}=={data5}: {data1==data5}")
    print(f"data2==data1 | {data1}=={data5}: {data2==data1}")
    print(f"data3==data1 | {data3}=={data1}: {data3==data1}")
    print(f"data4==data1 | {data4}=={data1}: {data4==data1}")
    print(f"data5==data1 | {data5}=={data1}: {data5==data1}")

    print("\n")

    print(f"data1!=data2 | {data1}!={data2}: {data1!=data2}")
    print(f"data1!=data3 | {data1}!={data3}: {data1!=data3}")
    print(f"data1!=data4 | {data1}!={data4}: {data1!=data4}")
    print(f"data1!=data5 | {data1}!={data5}: {data1!=data5}")
    print(f"data2!=data1 | {data1}!={data5}: {data2!=data1}")
    print(f"data3!=data1 | {data3}!={data1}: {data3!=data1}")
    print(f"data4!=data1 | {data4}!={data1}: {data4!=data1}")
    print(f"data5!=data1 | {data5}!={data1}: {data5!=data1}")

    print("\n")

    print(f"data1>=data2 | {data1}>={data2}: {data1>=data2}")
    print(f"data1>=data3 | {data1}>={data3}: {data1>=data3}")
    print(f"data1>=data4 | {data1}>={data4}: {data1>=data4}")
    print(f"data1>=data5 | {data1}>={data5}: {data1>=data5}")
    print(f"data2>=data1 | {data1}>={data5}: {data2>=data1}")
    print(f"data3>=data1 | {data3}>={data1}: {data3>=data1}")
    print(f"data4>=data1 | {data4}>={data1}: {data4>=data1}")
    print(f"data5>=data1 | {data5}>={data1}: {data5>=data1}")

    print("\n")

    print(f"data1>data2 | {data1}>{data2}: {data1>data2}")
    print(f"data1>data3 | {data1}>{data3}: {data1>data3}")
    print(f"data1>data4 | {data1}>{data4}: {data1>data4}")
    print(f"data1>data5 | {data1}>{data5}: {data1>data5}")
    print(f"data2>data1 | {data1}>{data5}: {data2>data1}")
    print(f"data3>data1 | {data3}>{data1}: {data3>data1}")
    print(f"data4>data1 | {data4}>{data1}: {data4>data1}")
    print(f"data5>data1 | {data5}>{data1}: {data5>data1}")

if __name__=="__main__":

    data1=Data(1999,1,1)
    data2=Data(2000,1,1)
    data3=Data(1999,2,1)
    data4=Data(1999,1,2)
    data5=Data(1999,1,1)
    func(data1, data2, data3, data4, data5)