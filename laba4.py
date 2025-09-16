import time
import math
import json

class Circle:
    def __init__(self, radius):
        if radius <= 0:
            raise ValueError("радиус должен быть положительным")
        self.radius = radius
    
    def area(self):
        return math.pi * self.radius ** 2
    
    def circumference(self):
        return 2 * math.pi * self.radius

class TrafficLight:
    __color = 'красный'
    __order = ['красный', 'желтый', 'зеленый']
    __times = {'красный': 7, 'желтый': 2, 'зеленый': 5}
    
    def running(self):
        for color in self.__order:
            self.__color = color
            print(f'светофор переключился на {color}')
            time.sleep(self.__times[color])

class Vehicle:
    def __init__(self, speed, cost_per_km):
        self.speed = speed
        self.cost_per_km = cost_per_km
    
    def travel_info(self, distance):
        time = distance / self.speed
        cost = distance * self.cost_per_km
        return time, cost
    
    def movement_method(self):
        return "базовый способ передвижения"
    
    def write_to_file(self, data, filename):
        with open(filename, 'w') as f:
            json.dump(data, f)

class Airplane(Vehicle):
    def __init__(self):
        super().__init__(800, 5)
    
    def movement_method(self):
        return "полет"

class Train(Vehicle):
    def __init__(self):
        super().__init__(120, 2)
    
    def movement_method(self):
        return "движение по рельсам"

class Car(Vehicle):
    def __init__(self):
        super().__init__(90, 3)
    
    def movement_method(self):
        return "езда по дорогам"

class CustomClass:
    class_var = 0
    
    def __init__(self, value):
        self.value = value
    
    def instance_method(self):
        return self.value * 2
    
    @classmethod
    def class_method(cls):
        cls.class_var += 1
        return cls.class_var
    
    @staticmethod
    def static_method(x, y):
        return x + y

def main():
    task = int(input('выберите задание (1-4): '))
    
    if task == 1:
        r = float(input('введите радиус: '))
        try:
            c = Circle(r)
            print(f'площадь: {c.area():.2f}')
            print(f'длина окружности: {c.circumference():.2f}')
        except ValueError as e:
            print(e)
    
    elif task == 2:
        tl = TrafficLight()
        tl.running()
    
    elif task == 3:
        distance = float(input('введите расстояние в км: '))
        
        vehicles = [Airplane(), Train(), Car()]
        results = []
        
        for vehicle in vehicles:
            t, c = vehicle.travel_info(distance)
            results.append({
                'type': vehicle.__class__.__name__,
                'time': t,
                'cost': c,
                'method': vehicle.movement_method()
            })
        
        fastest = min(results, key=lambda x: x['time'])
        cheapest = min(results, key=lambda x: x['cost'])
        
        print(f'самый быстрый: {fastest["type"]} - {fastest["time"]:.2f} часов')
        print(f'самый дешевый: {cheapest["type"]} - {cheapest["cost"]:.2f} руб')
        
        vehicle = vehicles[0]
        vehicle.write_to_file(results, 'transport.json')
    
    elif task == 4:
        obj = CustomClass(5)
        print(f'метод экземпляра: {obj.instance_method()}')
        print(f'метод класса: {CustomClass.class_method()}')
        print(f'статический метод: {CustomClass.static_method(3, 4)}')

if __name__ == '__main__':
    main()