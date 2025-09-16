def fib_sum(n):
    a, b, s = 0, 1, 0
    for _ in range(n):
        s += a
        a, b = b, a + b
    return s

def process_arg(arg):
    if type(arg) == tuple:
        return sum(len(str(x)) for x in arg if type(x) == str)
    elif type(arg) == list:
        letters = 0
        numbers = 0
        for x in arg:
            if type(x) == str:
                letters += len(x)
            elif type(x) == int or type(x) == float:
                numbers += 1
        return letters, numbers
    elif type(arg) == int or type(arg) == float:
        return sum(int(d) for d in str(arg) if int(d) % 2 != 0)
    elif type(arg) == str:
        return len([c for c in arg if c.isalpha()])
    else:
        return None

def matrix_positive_check_and_negate(matrix):
    for row in matrix:
        if not any(x > 0 for x in row):
            return matrix
    return [[-x for x in row] for row in matrix]

def demo_exceptions():
    try:
        1 / 0
    except ZeroDivisionError:
        print('произошло деление на ноль')
    finally:
        print('блок finally выполнен')

def main():
    t = int(input('выберите задание (1-4): '))
    if t == 1:
        n = int(input('введите n: '))
        print(f'сумма: {fib_sum(n)}')
    elif t == 2:
        arg = eval(input('введите аргумент: '))
        print(f'результат: {process_arg(arg)}')
    elif t == 3:
        rows = int(input('количество строк: '))
        matrix = []
        for i in range(rows):
            row = list(map(int, input(f'строка {i+1}: ').split()))
            matrix.append(row)
        result = matrix_positive_check_and_negate(matrix)
        print('результат:')
        for row in result:
            print(row)
    elif t == 4:
        demo_exceptions()

if __name__ == '__main__':
    main()