# Постановка задачи

Требуется реализовать простейший шедулер, распределяющий системные ресурсы на решение задач, поступающих в реальном времени. Время предполагается дискретным. В единицу времени может выполняться любое количество задач, при условии, что суммарное потребляемое количество ресурсов не больше, чем ресурсы системы. В каждый момент времени можно добавлять задачи для исполнения, причем только те, время появления которых не больше текущего. В каждый момент времени исполняемую задачу можно прервать и продолжить исполнение позже без потери прогресса. Цель задачи минимизировать целевую функцию <img src="https://render.githubusercontent.com/render/math?math=loss=\sum_{i}p_{i}\cdot\frac{f_{i} - t_{i}}{d_{i}}">, где за <img src="https://render.githubusercontent.com/render/math?math=f_{i}"> обозначен момент времени, в котороый задача была выполнена, <img src="https://render.githubusercontent.com/render/math?math=t_{i}"> -- это время появления задачи, <img src="https://render.githubusercontent.com/render/math?math=p_{i}"> -- приоритет задачи, <img src="https://render.githubusercontent.com/render/math?math=d_{i}"> -- время выполнения задачи в условных единицах времени

# Формат ввода

В первой строке задано положительное число <img src="https://render.githubusercontent.com/render/math?math=R, 0 < R \leq 1000"> -- численная характеристика системных ресурсов  
Во второй строке задано положительное число <img src="https://render.githubusercontent.com/render/math?math=N, 0 < N \leq 1000"> -- количество задач  
Следующие <img src="https://render.githubusercontent.com/render/math?math=N"> строк содержат четыре числа, которые описывают каждую задачу <img src="https://render.githubusercontent.com/render/math?math=t_{i}\:p_{i}\:d_{i}\:r_{i}">, где <img src="https://render.githubusercontent.com/render/math?math=r_{i}"> -- количество системных ресурсов на единицу времени, которое требуется для выполнения задачи, <img src="https://render.githubusercontent.com/render/math?math=0 < t_{i},p_{i},d_{i},r_{i} \leq 100">  
Строки с описанием задач отсортированы по возрастанию времени появления

# Формат вывода
<img src="https://render.githubusercontent.com/render/math?math=N"> строк, в формате "Число_стадий Начало_стадии_1 Конец_стадии_1 Начало_стадии_2 Конец_стадии_2 ..."

# Пример ввода
```
40  
10  
1 13 45 9  
1 14 50 9  
3 3 38 4  
3 8 11 4  
4 10 41 6  
4 10 10 8  
8 10 41 3  
8 10 24 9  
7 16 48 7  
10 10 30 2  
```
# Пример вывода
