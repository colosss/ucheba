class Thing:
    def __init__(self, name, price):
        self.name=name
        self.price=price
        print(f"Создание вещи {self.name} | {self.price}")

    def __del__(self):
        print(f"Удалние вещи {self.name} | {self.price}")
    def __str__(self):
        return f"{self.name} | {self.price}"

class Spoon(Thing):
    def __init__(self, name = "Ложка", price = 100):
        super().__init__(name, price)
        print(f"Создание ложки {self.name} | {self.price}")

    def __del__(self):
        print(f"Удаление ложки {self.name} | {self.price}")

        
class Knife(Thing):
    def __init__(self, name = "Нож", price = 100):
        super().__init__(name, price)
        print(f"Создание ножа {self.name} | {self.price}")

    def __del__(self):
        print(f"Удаление ножа {self.name} | {self.price}")


class Fork(Thing):
    def __init__(self, name="Вилка", price=100):
        super().__init__(name, price)
        print(f"Создание вилки {self.name} | {self.price}")

    def __del__(self):
        print(f"Удаление вилки {self.name} | {self.price}")


class Stol:
    def __init__(self, max_count):
        self.max_count=max_count
        self.item=[]
        print(f"Создание стол | max_count={self.max_count}")
    def __del__(self):
        print("Удалние стола")
    def put(self, thing):
        if len(self.item)>=self.max_count:
            print(f"Ошибка, стол переполнен, максимальное число предметов = {self.max_count}, число предметов на столе = {len(self.item)}")
            return False
        else:
            self.item.append(thing)
            print(f"На стол положена: {thing}")
            return True
    def remove(self, item_or_name):
        for item in self.item[:]:
            if item is item_or_name or item.name == item_or_name:
                print(f"Удаление со стола {item}")
                self.item.remove(item)
                return True
        print(f"Вещь {item_or_name} не найдена на столе")
        return False
    def find_by_name(self, name):
        found=[item for item in self.item if item.name==name]
        if found: return found
        return False
    def find_by_price(self, price):
        found=[item for item in self.item if item.price==price]
        if found: return found
        return False
    def total_cost(self):
        return sum(item.price for item in self.item)
    def __str__(self):
        if not self.item:
            return "Стол пуст"
        line=[f"Стол (max:{self.max_count}): "]
        for i,item in enumerate(self.item, 1):
            line.append(f"{i}.{item}")
        line.append(f"Общая стоимость: {self.total_cost()}")
        return "\n".join(line)
    
if __name__=="__main__":
    table = Stol(max_count=5)

    spoon1 = Spoon("Ложка чайная", 120)
    spoon2 = Spoon("Ложка столовая", 150)
    fork1 = Fork("Вилка", 180)
    knife1 = Knife("Нож", 200)

    table.put(spoon1)
    table.put(spoon2)
    table.put(fork1)
    table.put(knife1)

    extra = Spoon("Ложка десертная", 130)
    table.put(extra)

    table.put(Spoon("Ложка лишняя", 100))

    print("\nТекущее состояние:")
    print(table)

    print("\nПоиск по имени 'Ложка чайная':")
    found = table.find_by_name("Ложка чайная")
    if found:
        for f in found:
            print(f"Найдено: {f}")

    print("\nПоиск по цене 180 руб.:")
    found = table.find_by_price(180)
    if found:
        for f in found:
            print(f"Найдено: {f}")

    table.remove("Вилка")

    print("\nПосле удаления:")
    print(table)
    
    del table
    del spoon1, spoon2, fork1, knife1, extra

