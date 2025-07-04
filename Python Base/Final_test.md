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
