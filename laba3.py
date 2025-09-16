import json
import os

def task1():
    with open('F1.txt', 'w') as f1:
        while True:
            line = input('введите строку: ')
            if line == '':
                break
            f1.write(line + '\n')
    
    with open('F1.txt', 'r') as f1, open('F2.txt', 'w') as f2:
        lines = f1.readlines()
        if len(lines) >= 4:
            f2.writelines(lines[3:])
    
    with open('F2.txt', 'r') as f2:
        first_line = f2.readline()
        word_count = len(first_line.split())
        print(f'количество слов: {word_count}')

def task2():
    trans = {'One': 'Один', 'Two': 'Два', 'Three': 'Три', 'Four': 'Четыре'}
    
    try:
        with open('english_numbers.txt', 'r') as f_in:
            with open('russian_numbers.txt', 'w') as f_out:
                for line in f_in:
                    parts = line.split(' — ')
                    if parts[0] in trans:
                        new_line = trans[parts[0]] + ' — ' + parts[1]
                        f_out.write(new_line)
    except FileNotFoundError:
        print('файл не найден')

def task3():
    subjects = {}
    try:
        with open('subjects.txt', 'r', encoding='utf-8') as f:
            for line in f:
                parts = line.split(':')
                name = parts[0]
                hours = 0
                for part in parts[1].split():
                    if '(' in part:
                        num = part.split('(')[0]
                        hours += int(num)
                subjects[name] = hours
        print(subjects)
    except FileNotFoundError:
        print('файл не найден')

def task4():
    firms = {}
    total_profit = 0
    count_profit = 0
    
    try:
        with open('firms.txt', 'r', encoding='utf-8') as f:
            for line in f:
                data = line.split()
                name = data[0]
                revenue = int(data[2])
                costs = int(data[3])
                profit = revenue - costs
                firms[name] = profit
                if profit > 0:
                    total_profit += profit
                    count_profit += 1
    except FileNotFoundError:
        print('файл не найден')
        return
    
    avg_profit = total_profit / count_profit if count_profit > 0 else 0
    result = [firms, {'average_profit': avg_profit}]
    
    with open('firms.json', 'w') as f_json:
        json.dump(result, f_json)

def main():
    t = int(input('выберите задание (1-4): '))
    if t == 1:
        task1()
    elif t == 2:
        task2()
    elif t == 3:
        task3()
    elif t == 4:
        task4()

if __name__ == '__main__':
    main()