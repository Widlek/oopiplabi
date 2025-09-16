def task1():
    try:
        num = int(input("Введите число: "))
        if num == 0:
            print("Неверный ввод!")
            return
            
        divisors = []
        for i in range(1, int(abs(num)**0.5) + 1):
            if num % i == 0:
                divisors.append(int(num / i))
                divisors.append(i)
        divisors.sort()
        print(f"Делители числа {num}: {divisors}")
    except ValueError:
        print("введите целое число")

def task2():
    text = input("Введите строку: ").strip()
    
    if not text:
        print("Строка пуста")
        return
    
    words = text.split()
    print(f"Количество слов: {len(words)}")
    
    if words:
        longest_word = max(words, key=len)
        print(f"Самое длинное слово: {longest_word}")

def task3():
    try:
        n = int(input("Введите количество чисел (n ≥ 2): "))
        if n < 2:
            print("Ошибка: n должно быть ≥ 2")
            return
            
        numbers = []
        for i in range(n):
            num = int(input(f"Введите число {i+1}: "))
            numbers.append(num)
            
        sums = []
        for i in range(len(numbers) - 1):
            sums.append(numbers[i] + numbers[i+1])
            
        print(f"Список сумм соседних чисел: {sums}")
    except ValueError:
        print("Ошибка: введите целые числа")

def task4():
    sample_dict = {
        'b': 15,
        'a': 30,
        'd': 10,
        'c': 25
    }
    
    print(f"Исходный словарь: {sample_dict}")
    
    sorted_asc = dict(sorted(sample_dict.items(), key=lambda x: x[0]))
    print(f"По возрастанию: {sorted_asc}")
    
    sorted_desc = dict(sorted(sample_dict.items(), key=lambda x: x[0], reverse=True))
    print(f"По убыванию: {sorted_desc}")
    
    max_key = max(sample_dict, key=sample_dict.get)
    print(f"Элемент с максимальным значением: '{max_key}': {sample_dict[max_key]}")

def task5():

    products = {
        "торт": ["бисквит, крем, ягоды", 50.0, 1000],
        "пирожное": ["песочное тесто, крем", 30.0, 500],
        "маффин": ["шоколад, орехи", 25.0, 800],
        "эклер": ["заварное тесто, крем", 35.0, 600]
    }
    
    cart = {} 
    
    while True:
        print("\n--- Кондитерская ---")
        print("1. Просмотр описания")
        print("2. Просмотр цены")
        print("3. Просмотр количества")
        print("4. Вся информация")
        print("5. Покупка")
        print("6. Выход")
        
        choice = input("Выберите пункт меню: ")
        
        if choice == '1':
            for product, details in products.items():
                print(f"{product}: {details[0]}")
                
        elif choice == '2':
            for product, details in products.items():
                print(f"{product}: {details[1]} руб. за 100г")
                
        elif choice == '3':
            for product, details in products.items():
                print(f"{product}: {details[2]}г")
                
        elif choice == '4':
            for product, details in products.items():
                print(f"{product}: состав - {details[0]}, цена - {details[1]} руб./100г, количество - {details[2]}г")
                
        elif choice == '5':
            total_cost = 0
            while True:
                product = input("Введите название продукта: ").strip()
                if product.lower() == 'n':
                    break
                    
                if product not in products:
                    print("Такого продукта нет в ассортименте")
                    continue
                    
                try:
                    quantity = float(input("Введите количество в граммах: "))
                    if quantity <= 0:
                        print("Количество должно быть положительным")
                        continue
                        
                    available = products[product][2]
                    if quantity > available:
                        print(f"Недостаточно товара. Доступно: {available}г")
                        continue

                    if product in cart:
                        cart[product] += quantity
                    else:
                        cart[product] = quantity
                        
                    products[product][2] -= quantity
                    
                    cost = quantity * products[product][1] / 100
                    total_cost += cost
                    print(f"Добавлено: {quantity}г {product} за {cost:.2f} руб.")
                    
                except ValueError:
                    print("Ошибка: введите числовое значение")
            

            if cart:
                print("\n--- Чек ---")
                for product, quantity in cart.items():
                    cost = quantity * products[product][1] / 100
                    print(f"{product}: {quantity}г - {cost:.2f} руб.")
                print(f"Итого: {total_cost:.2f} руб.")
            else:
                print("Корзина пуста")
                
        elif choice == '6':
            break
            
        else:
            print("Неверный выбор. Попробуйте снова.")

def task6():
    """Сортировка кортежа и вывод первого и последнего элемента"""
    try:
        numbers = tuple(map(int, input("Введите целые числа через пробел: ").split()))
        
        if not numbers:
            print("Кортеж пуст")
            return
            
        sorted_tuple = tuple(sorted(numbers, reverse=True))
        print(f"Отсортированный кортеж: {sorted_tuple}")
        print(f"Первый элемент: {sorted_tuple[0]}")
        print(f"Последний элемент: {sorted_tuple[-1]}")
    except ValueError:
        print("Ошибка: введите целые числа через пробел")

def main():
    """Главное меню"""
    tasks = {
        '1': task1,
        '2': task2,
        '3': task3,
        '4': task4,
        '5': task5,
        '6': task6
    }
    
    while True:
        print("\n=== Выберите задачу ===")
        print("1. Делители числа")
        print("2. Работа со строкой")
        print("3. Суммы соседних чисел")
        print("4. Сортировка словаря")
        print("5. Кондитерская")
        print("6. Сортировка кортежа")
        print("0. Выход")
        
        choice = input("Ваш выбор: ")
        
        if choice == '0':
            print("До свидания!")
            break
            
        if choice in tasks:
            tasks[choice]()
        else:
            print("Неверный выбор. Попробуйте снова.")

if __name__ == "__main__":
    main()