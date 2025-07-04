# Итоговый тест

## Группа А

### Задание 1

![image](https://github.com/user-attachments/assets/c415ddbd-583b-40f9-bf50-66b8facc642d)

### Задание 2

![image](https://github.com/user-attachments/assets/0606fbf1-3655-4861-bea2-a3dbd77723a7)

### Задание 3

![image](https://github.com/user-attachments/assets/7acd8306-77fd-48f2-ac48-cf8966ddcf8c)

### Задание 4

![image](https://github.com/user-attachments/assets/d818a533-c492-40ff-8204-4d02f730446c)

```py
a = int(input())
b = int(input())
c = int(input())
print(a//b)
print(b%c)
```
### Задание 5


str() - команда, которая переводит что угодно в строку (string), например из числа 1000.101 мы получим строку '100.101'

### Задание 6

![image](https://github.com/user-attachments/assets/1c488696-c2e6-4d88-afa0-754d8e75702f)

```py
a = int(input())
b = int(input())
c = int(input())

print(f"{a} * ({b} + {c}) = {a*(b+c)}")
```

### Задание 7

![image](https://github.com/user-attachments/assets/1883140b-c509-45a8-a52a-97d7b1eb62eb)

### Задание 8

![image](https://github.com/user-attachments/assets/c02ea718-cc9f-43fa-a1a4-12e13144724e)

```py
n = int(input())

if n > 0 and n % 2 == 0:
    print("YES")
else:
    print("NO")
```

### Задание 9

![image](https://github.com/user-attachments/assets/2bea2943-b3d8-4fe6-8614-1d175438534d)

```py
n = input()

if n == "RED" or n == "red":
    print("Красный")
elif n == "GREEN" or n == "green":
    print("Зеленый")
elif n == "YELLOW" or n == "yellow":
    print("Желтый")
else:
    print("Ошибка")
```

### Задание 10

![image](https://github.com/user-attachments/assets/03c93870-a2d0-4bec-abd5-0366b26d2b44)

```py
for i in range(с_какого_элемента_начинаем, ДО_какого_элемена_делаем, шаг):
    действие
```

Цикл for выполняет действие пока i принимает значения от с_какого_элемента_начинаем до ДО_какого_элемена_делаем с шагом шаг.

### Задание 11

![image](https://github.com/user-attachments/assets/8866b830-515a-40b8-88c6-b54953739f64)

### Задание 12

![image](https://github.com/user-attachments/assets/d7a5224a-20c6-4ca0-afe9-05087cce067c)

```py
string = input()

for i in range(len(string)):
    print(string[i], end= " ")
```

### Задание 13

![image](https://github.com/user-attachments/assets/c48306a2-c040-4746-a894-35df1c343b1e)

```py
a = input().split(":")
summ = 0
for i in range(len(a)):
    summ += int(a[i])
print(summ)
```

## Группа В

### Задание 1

![image](https://github.com/user-attachments/assets/25bf8cad-7201-498c-b45c-689a1a08d44c)

### Задание 2

![image](https://github.com/user-attachments/assets/83c76725-5c38-4b56-9ba7-c9d28faf15c4)

```py
a = input()
for i in range(len(a)):
    b = a[i]
    if (i == 2):
        b = 'G'
    if i == 5:
        b = 'I'
    if i == len(a)-1:
        b = 'R'
    print(b, end="")
```

### Задание 3

![image](https://github.com/user-attachments/assets/dc048944-aa91-4911-9c6c-65005c90a7a3)

```py
n = int(input())
for i in range(1, n+1):
    if n % i == 0:
        print(i, end= " ")
```

### Задание 4

![image](https://github.com/user-attachments/assets/b24d7065-2381-410e-98d8-1d5f8caaab8e)

```py
N = int(input()) # Вводим количество столбцов в матрице
M = N # Вводим количество строк в матрице
matrix = [] # Матрица (Двумерный массив)
for i in range(N):
    row = [] # Строка в матрице (Одномерный массив)
    for j in range(M):
        if i >= j:
            row.append(1)
        else:
            row.append(0)
    matrix.append(row) # Добавление строки в матрицу


for i in range(N):
    for j in range(M):
        if j == M-1:
            print(matrix[i][j])
        else:
            print(matrix[i][j], end=" ")
```

### Задание 5

![image](https://github.com/user-attachments/assets/11f35737-86b2-4d74-8dc2-e98168227761)

```py
N = int(input()) # Вводим количество столбцов в матрице
M = int(input()) # Вводим количество строк в матрице
matrix = [] # Матрица (Двумерный массив)
for i in range(N):
    row = [] # Строка в матрице (Одномерный массив)
    for j in range(M):
        row.append(i+j)
    matrix.append(row) # Добавление строки в матрицу


for i in range(N):
    for j in range(M):
        if j == M-1:
            print(matrix[i][j])
        else:
            print(matrix[i][j], end=" ")
```

### Задание 6

![image](https://github.com/user-attachments/assets/e0278ad8-ee7c-4626-a7d5-8b8ffa7e501e)

tuple.index(a) - Индекс под которым встречается переменная равная a в кортеже tuple. Например если tuple = (1, 2, 3, 'a', 'b', 'c') и a = 'a', то tuple.index(a) = 3

### Задание 7

![image](https://github.com/user-attachments/assets/2987e338-9323-4bb7-835d-fd94e123486d)

```py
tuplea = tuple(input().split())
tupleb = tuple(input().split())
tuplec = tuple(input().split())

print(tuplea*3 + tupleb*2 + tuplec)
```

### Задание 8

![image](https://github.com/user-attachments/assets/03cff645-6546-4fdd-8b22-502fad6700d6)

Команда remove() удаляет элемент из множества. Если такого элемента в наборе не окажется, то программа выдаст ошибку.

```py
s = {1, 2, 3, 4, 6}
s.remove(5) # ОШИБКА - KeyError: 5
```

### Задание 9

![image](https://github.com/user-attachments/assets/95ce5100-0b56-4862-9fd5-88ac730d24c1)

### Задание 10

![image](https://github.com/user-attachments/assets/7dc6059a-71d9-42c7-8c2d-8646c7582868)

```py
a = set(input())
b = set(input())

if a.issubset(b):
    print("YES")
else:
    print("NO")
```

### Задание 11

![image](https://github.com/user-attachments/assets/ff4c0ec7-7e1f-4f3e-a27e-bf596365ee04)

```py
seta = set(input())
setb = set(input())

# Напишите в setc множество обших элементов
setc = seta & setb

# ВЫВОД НЕ МЕНЯТЬ
b = []
for i in range(len(setc)):
    b.append(int(setc.pop()))

b.sort()
for i in range(len(b)):
    print(b[i], end= " ")
```

## Группа С

### Задание 1

![image](https://github.com/user-attachments/assets/b9312447-850d-42a3-8bb2-35770d906d95)

```py
def printa(n, m):
    for i in range(n):
        print("*"*m)

n = int(input())
m = int(input())
printa(n, m)
```

### Задание 2

![image](https://github.com/user-attachments/assets/55d58d7c-a2ed-4065-a079-2bd3e6b25212)

```py
# Ввод НЕ МЕНЯТЬ
n = int(input())
students = []
for i in range(n):
    names = {}
    name, surname, years = input().split()
    names['name'], names['surname'], names['years'] = name, surname, int(years)
    students.append(names)

# В массиве students хранятся словари
# Например:
# students = [
#     {'name': 'Ivan', 'surname' : 'Ivanov', 'years' : '15'},
#     {'name': 'Sasha', 'surname' : 'Pupkin', 'years' : '17'}
# ]

# Напишите ваш код здесь


for i in range(len(students)):
    print("B", 2025 - students[i]['years'], "году родился", students[i]['name'])
```

