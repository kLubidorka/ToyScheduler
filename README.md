# Toy scheduler
Реализация простейшего планировщика 
## Запуск бенчмарка
### Mac / Linux
```bash
./run_benchmark.sh NUM_TESTS
```
Где `NUM_TESTS` -- число тестов, которое будет сгенерировано для запуска решений. Тесты генерируются автоматически. Параметры генерации можно настроить в `run_benchmark.cpp`.  
  
После сборки и запуска бенчмарка будут созданы следующие директории:  
* `build/tests/` -- сгенерированные тесты,  
* `build/{SOLUTION_NAME}Reports/` -- вердикты чекера для решения `SOLUTION_NAME` на всех тестах,  
* `build/{SOLUTION_NAME}Solutions/` -- результаты работы планировщика `SOLUTION_NAME` на всех тестах
  
На данный момент доступно два решения `greedy` и `knapsack`

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
20
5
2 18 2 9
3 20 9 3
5 5 10 2
6 16 6 9
8 19 8 8
```
# Пример вывода
```
1 2 4 
1 3 12 
2 5 8 12 19 
1 6 12 
1 8 16 
```
# Описание решения

В проекте есть 2 решения задачи: методом динамического программирования и жадными алгоритмами. Для начала разберем общую часть решения. Пусть в текущий момент времени есть какой-то набор задач J, состоящий из <img src="https://render.githubusercontent.com/render/math?math=(t_j, p_j, d_j, r_j)">, 1 <= j <= |J|, также заметим, что если мы не возьмем на исполнение задачу номер j, то loss увеличится на <img src="https://render.githubusercontent.com/render/math?math=\frac{p_{j}}{d_{j}}">. В таком случае нам нужно выбрать <img src="https://render.githubusercontent.com/render/math?math=x_j \in {0, 1}"> так, чтобы <img src="https://render.githubusercontent.com/render/math?math=\sum_{j}x_j r_j \leq R">, и  при этом  <img src="https://render.githubusercontent.com/render/math?math=\sum_{j}(1 - x_j) \frac{p_{j}}{d_{j}} \rightarrow min">

1) Метод динамического программирования

Это классическая задача о рюкзаке, где вес предмета - <img src="https://render.githubusercontent.com/render/math?math=r_j">, а его стоимость - <img src="https://render.githubusercontent.com/render/math?math=\frac{p_{j}}{d_{j}}">. Таким образом можно выбирать исполняемые задачи на 1 такт времени. После чего добавлять новопришедшие задачи и удалять законченные. Асимптотика - O(T * N * R), где T - суммарное время работы

2) Жадный алгоритм

В каждый момент времени будем сортировать все незаконченные работы по <img src="https://render.githubusercontent.com/render/math?math=\frac{p_{j}}{d_{j}}">, после чего жадно их класть на исполнение. Тут же можно заметить, что мы можем проскакивать время не по одному такту, а только те моменты, где заканчивается / добавляется новая задача. Асимптотика - O(N^2)
