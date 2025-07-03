# Группа А

## Задание 1

![image](https://github.com/user-attachments/assets/27a282a9-6b08-4eb2-8418-bf1afc6f7af6)

```py
n = int(input())
summ = 0
for i in range(n):
    summ += int(input())
print(summ)
```

## Задание 2

![image](https://github.com/user-attachments/assets/a6fcc6dd-dc6a-4117-901d-c41768a26939)

```py
def temp(a):
    summ = 0
    for i in range(len(a)):
        if (int(a[i]) > 5):
            summ +=1
    return(summ)

a = input().split()
print(temp(a))
```

## Задание 3

![image](https://github.com/user-attachments/assets/03ee7996-e014-4ecf-a067-d97d448a3cfd)

```py
def temp(a):
    a = a.split()
    summ = 0
    for i in range(len(a)):
        if (int(a[i]) > 5):
            summ +=1
    return summ

n = int(input())
for i in range(n):
    a = input()
    print(temp(a))
```

## Задание 4

![image](https://github.com/user-attachments/assets/087cdd6e-dcd3-4a9b-93f0-59e0dfb587ca)

```py
def calculator(array):
    if (array[1] == "Плюс"):
        return int(array[0]) + int(array[2])
    elif (array[1] == "Минус"):
        return int(array[0]) - int(array[2])
    elif (array[1] == "Делить"):
        if int(array[2]) == 0:
            return "Ошибка"
        return int(array[0]) / int(array[2])
    elif (array[1] == "Умножить"):
        return int(array[0]) * int(array[2])
    else:
        return "Ошибка"
    

a = input().split()
print(calculator(a))
```

## Задание 5

![image](https://github.com/user-attachments/assets/a19b2a78-c71f-4481-a49e-c4bb2163d988)

```py
def calculator(array):
    if (array[1] == "Плюс"):
        return int(array[0]) + int(array[2])
    elif (array[1] == "Минус"):
        return int(array[0]) - int(array[2])
    elif (array[1] == "Делить"):
        if int(array[2]) == 0:
            return "Ошибка"
        return int(array[0]) / int(array[2])
    elif (array[1] == "Умножить"):
        return int(array[0]) * int(array[2])
    else:
        return "Ошибка"
    
n = int(input())
for i in range(n):
    a = input().split()
    print(calculator(a))

```

## Задание 6

![image](https://github.com/user-attachments/assets/6c04b9d4-afb0-470b-a039-4ccdd6132de9)

```py
n = int(input())

matrix = []
for i in range(n):
    row = []
    for j in range(n):
        if i == 0 or j == 0 or i == n-1 or j == n-1:
            row.append(1)
        else:
            row.append(0)
    matrix.append(row)



# Вывод матрицы. Заменить только matrix на имя вашей матрицы (Остальное не менять)
for i in range(n):
    for j in range(n):
        if j == n-1:
            print(matrix[i][j])
        else:
            print(matrix[i][j], end=" ")
```

## Задание 7

![image](https://github.com/user-attachments/assets/02586eae-72ff-4a41-8530-6b92aaf24be8)

```py
def print_matrix(n):
    matrix = []
    for i in range(n):
        row = []
        for j in range(n):
            if i == 0 or j == 0 or i == n-1 or j == n-1:
                row.append(1)
            else:
                row.append(0)
        matrix.append(row)

    for i in range(n):
        for j in range(n):
            if j == n-1:
                print(matrix[i][j])
            else:
                print(matrix[i][j], end=" ")
                
a = int(input())
for i in range(a):
    print_matrix(int(input()))
```

## Задание 8

![image](https://github.com/user-attachments/assets/6d0b2923-9189-4723-a0da-71d4a5b88f64)

```py
a = int(input())
m=[]
for i in range(a):
    r=input().split()
    m.append(r)
minn = 1000
for i in range(a):
    for j in range(a):
        if (int(m[i][j]) < minn) and i <= j:
            minn = int(m[i][j])
print(minn)
```

## Задание 9

![image](https://github.com/user-attachments/assets/46a31224-8342-41c7-b154-3680fc7b27bd)

```py
n = int(input())

for i in range(n):
    tuple1 = tuple(input())
    print(tuple1, len(tuple1))
```

## Задание 10

![image](https://github.com/user-attachments/assets/7c1a1d44-d736-48d1-bb7c-2d0cf6558922)

```py
a = input().split()
a0 = int(a[0])
a1 = int(a[1])
tuplea = (a0, a1, a0 // a1, a0 % a1)
print(tuplea)
```

## Задание 11

![image](https://github.com/user-attachments/assets/b7506ca0-28de-49ed-a525-7254f554a955)

```py
a = input().split()
b = input().split()
tuple1 = tuple(a)
tuple2 = tuple(b)
print(tuple1 + tuple2)
```

# Группа В

## Задание 1

![image](https://github.com/user-attachments/assets/636a01c1-0470-4637-9f88-ab59fa01a330)

```py
a = set(input())
b = set(input())

if a.issubset(b):
    print("YES")
else:
    print("NO")
```

## Задание 2

![image](https://github.com/user-attachments/assets/b5a428a2-540e-454d-b395-6a0fd3cba0e4)

```py
a = set(input())
b = set(input())
if a == b:
    print("YES")
else:
    print("NO")
```

## Задание 3

![image](https://github.com/user-attachments/assets/db5bf66a-b1d8-4a73-83d2-4c0a7281bdb2)

```py
# Напишите ваш код
a = input().split("*")
b = input().split("*")
seta = set(a)
setb = set(b)

# Напишите в setc множество обших элементов
setc = seta | setb

# ВЫВОД НЕ МЕНЯТЬ
b = []
for i in range(len(setc)):
    b.append(int(setc.pop()))

b.sort()
for i in range(len(b)):
    print(b[i], end= " ")
```

## Задание 4

![image](https://github.com/user-attachments/assets/399007ab-c601-4cf9-8952-74c5f8d3783b)

```py
# Напишите ваш код
a = input().split("_")
b = input().split("_")
c = input().split("_")
seta = set(a)
setb = set(b)
setc = set(c)

# Напишите в setc множество обших элементов
setc = seta & setb & setc

# ВЫВОД НЕ МЕНЯТЬ
b = []
for i in range(len(setc)):
    b.append(int(setc.pop()))

b.sort()
for i in range(len(b)):
    print(b[i], end= " ")
```

## Задание 5

![image](https://github.com/user-attachments/assets/f04bad9c-0d13-4d21-9f0d-4ab03c6acf5a)

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
    print(students[i]['name'], students[i]['surname'], "родился в", 2025 - students[i]['years'], "году")
```

## Задание 6

![image](https://github.com/user-attachments/assets/a7211580-035d-4e08-b3f8-4f36199bd510)

```py
def triangle(base, size):
    for i in range(size):
        print(base*(i+1))
base = input()
size = int(input())
triangle(base, size)
```
