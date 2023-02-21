## Задание

Задание состоит из двух программ, которые необходимо реализовать. Взаимодействие программ должно быть реализовано через использование сокетов.

## Программа №1.

Должна состоять из двух потоков и одного общего буфера.

Поток 1.  Принимает строку, которую введет пользователь.   Должна быть проверка, что строка состоит только из цифр и не превышает 64 символа. После проверки строка должна быть отсортирована по убыванию и все элементы, значение которых чётно, заменены на латинские буквы «КВ». После данная строка помещается в общий буфер и поток должен ожидать дальнейшего ввода пользователя.

Поток 2. Должен обрабатывать данные которые помещаются в общий буфер. После получения данных общий буфер затирается. Поток должен вывести полученные данные на экран, рассчитать  общую  сумму всех  элементов , которые являются численными значениями.  Полученную сумму передать в Программу №2. После этого поток ожидает следующие данные.

Примечание №1 по Программе №1: Взаимодействие потоков должно быть синхронизировано,  поток №2  не должен постоянно опрашивать общий буфер. Механизм синхронизации не должен быть глобальной переменной.
Примечание №2 по Программе №1: Работа программы должна быть максимально независима от статуса запуска программы №2. Это значит, что внезапный останов программы №2 не должен приводить к немедленным проблемам ввода у пользователя.
При перезапуске программы №2 необходимо произвести передподключение.

## Программа №2.

It Ожидает данные от  Программы №1. При получении  данных происходит анализ из скольки символов состоит  переданное значение. Если оно больше 2-ух символов и если оно кратно 32 выводит сообщение о полученных данных  , иначе выводится сообщение об ошибке. Далее программа продолжает ожидать данные.

Примечание №1 по Программе №2: Работа программы должна быть максимально независима от статуса запуска программы №1. Внезапный останов программы №1 не должен приводить к немедленным проблемам отображения. Необходимо ожидать подключение программы №1 при потере связи между программами.

Примечание по заданию: Не обязательно все размещать в одном классе. Может быть разработана иерархия классов. Чем более функционален интерфейс класса, тем лучше.

========================================================================================

## Task

The task consists of two programs that need to be implemented. The interaction of programs must be implemented through the use of sockets.

## Program number 1.

Must consist of two streams and one shared buffer.

Thread 1. Receives a string that the user will enter. There should be a check that the string consists only of numbers and does not exceed 64 characters. After checking, the string should be sorted in descending order and all elements whose value is even should be replaced with the Latin letters "KB". This string is then placed in a shared buffer and the thread must wait for further user input.

Thread 2. Must process the data that is placed in the shared buffer. After data is received, the shared buffer is overwritten. The thread should display the received data on the screen, calculate the total sum of all elements that are numerical values. Transfer the received amount to Program No. 2. The thread then waits for the next data.

Note #1 on Program #1: The interaction of threads must be synchronized, thread #2 should not constantly poll the shared buffer. The synchronization mechanism must not be a global variable.
Note #2 on Program #1: The operation of the program should be as independent as possible from the startup status of program #2. This means that the sudden stop of program #2 should not lead to immediate input problems for the user.
When restarting program No. 2, it is necessary to make a pre-connection.

## Program number 2.

It Waits for data from Program #1. When receiving data, an analysis is made of how many characters the transmitted value consists of. If it is more than 2 characters and if it is a multiple of 32, it displays a message about the data received, otherwise an error message is displayed. Then the program continues to wait for data.

Note #1 on Program #2: The operation of the program should be as independent as possible from the startup status of program #1. The sudden stop of program #1 should not lead to immediate display problems. It is necessary to wait for the connection of program No. 1 in case of loss of communication between programs.

Assignment Note: You don't have to put everything in the same class. A class hierarchy can be developed. The more functional a class interface is, the better.

========================================================================================

## NOTES from developer

Before submiting the string of numbers in program number 1, be sure to run program number 2; otherwise you may not be able to get the data in first trial.
Перед подачей строки чисел в программу №1 обязательно запустите программу №2; в противном случае вы не сможете получить данные в первой пробной версии.

The program is written to compile and run in linux.
Программа написана для компиляции и запуска в Linux.
