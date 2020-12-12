# ABC_MP2

МИКРОПРОЕТ ПО ДИСЦИПЛИНЕ "АРХИТЕКТУРА ВЫЧИСЛИТЕЛЬНЫХ СИСТЕМ"
=====================

В папке "Homework" хранятся четыре .bat файла для упрощения тестирования программы, .cpp файл с исходным кодом работы, .exe файл, три теста «testN.txt», где N – порядковый номер теста, Пояснительная записка.pdf – отчет о проделанной работе в формате pdf и Пояснительная записка.docx – отчет о проделанной работе в формате docx.

****

Цель работы
=====================

Разработка многопоточной программы с использованием семафоров.

Условие
=====================

Тема №5:

Задача о каннибалах. Племя из n дикарей ест вместе из большого горшка, который вмещает m кусков тушеного миссионера. Когда дикарь хочет обедать, он ест из горшка один кусок, если только горшок не пуст, иначе дикарь будит повара и ждет, пока тот не наполнит горшок. Повар, сварив обед, засыпает. Создать многопоточное приложение, моделирующее обед дикарей. При решении задачи пользоваться семафорами.

Работа с данными
=====================

Для работы с входными данными была использована файловая система. 

Все входные файлы имеют вид «testN.txt», где N – номер теста. Основная работа по считыванию данных из файла происходит в функции void workWithFiles(). В первой строке каждого файла располагаются два числа, введенные через пробел: m – максимальное количество кусков тушеного миссионера в горшке – и n – количество дикарей в племени. Далее в каждой строчке располагается команда типа «cannibal N is hungry», где N – это номер каннибала в племени. Оба числа должны быть целочисленными и иметь значение, строго большее нуля; также на N есть ограничение сверху: оно должно быть меньше либо равно количеству дикарей в племени.

Выходные данные реализованы с помощью вывода сообщений в консоль.

Формат взаимодействия с программой – ввод данных в консоль в формате «<имя .exe файла> <путь к входному файлу>». При некорректно заданных входных параметрах в консоль выводится сообщение о верном формате ввода. В случае ввода некорректных данных программа выводит пользователю сообщение о том, в каком формате должны вводиться входные данные и завершает свою работу.

Для ускорения тестирования были разработаны .bat файлы для тестирования корректных и некорректных входных данных. Для работы с .bat файлами необходимо открыть командную строку, изменить директорию на папку, содержащую .exe файл, «перетащить» нужный .bat файл в консоль и нажать Enter.

### Результат выполнения:

ТЕСТ 1:

Данный тест был разработан с целью показать, что будет происходить в случае ввода номеров тех дикарей, которых нет в племени.

.bat файл для тестирования продемонстрированных входных данных имеет название Correct_Input_test1.bat и содержит в себе текст «MP2.exe test1.txt».


Входные данные:

30 5

cannibal 1 is hungry

cannibal 2 is hungry

cannibal 3 is hungry

cannibal 4 is hungry

cannibal 5 is hungry

cannibal 6 is hungry

cannibal 7 is hungry


Выходные данные:


----------------------------------------------

UNEXPECTED EVENT! (which ID is 23324)

There aren't any food in the pot.
We woke up a cook. He made new portion
of stewed missionary and went to sleep again...

----------------------------------------------

EVENT 1! (which ID is 21800)

Cannibal 1 had a meal.
Now there are 29 pieces of stewed missionary.

----------------------------------------------

EVENT 2! (which ID is 11608)

Cannibal 2 had a meal.
Now there are 28 pieces of stewed missionary.

----------------------------------------------

EVENT 3! (which ID is 14004)

Cannibal 3 had a meal.
Now there are 27 pieces of stewed missionary.

----------------------------------------------

EVENT 4! (which ID is 13236)

Cannibal 4 had a meal.
Now there are 26 pieces of stewed missionary.

----------------------------------------------

EVENT 5! (which ID is 17544)

Cannibal 5 had a meal.
Now there are 25 pieces of stewed missionary.

----------------------------------------------

EVENT 6! (which ID is 11700)

Great pitty! Cannibal 6 does not leave
in this tribe, he cannot eat missionary's
meat with other savages...

----------------------------------------------

EVENT 7! (which ID is 17208)

Great pitty! Cannibal 7 does not leave
in this tribe, he cannot eat missionary's
meat with other savages...

----------------------------------------------

Time of program working = 0.017 sec

----------------------------------------------

****

ТЕСТ 2:

Данный тест был разработан с целью показать, что будет происходить в случае ввода отрицательных номеров дикарей, которых, естественно, нет в племени, а также с целью продемонстрировать, что будет, если в горшке закончится еда, а голодные каннибалы еще останутся.

.bat файл для тестирования продемонстрированных входных данных имеет название Correct_Input_test2.bat и содержит в себе текст «MP2.exe test2.txt».


Входные данные:

5 13

cannibal 1 is hungry

cannibal -2 is hungry

cannibal 3 is hungry

cannibal -4 is hungry

cannibal 5 is hungry

cannibal -6 is hungry

cannibal 7 is hungry


Выходные данные:


----------------------------------------------

UNEXPECTED EVENT! (which ID is 15332)

There aren't any food in the pot.
We woke up a cook. He made new portion
of stewed missionary and went to sleep again...

----------------------------------------------

EVENT 1! (which ID is 15592)

Cannibal 1 had a meal.
Now there are 4 pieces of stewed missionary.

----------------------------------------------

EVENT 2! (which ID is 14656)

Great pitty! Cannibal -2 does not leave
in this tribe, he cannot eat missionary's
meat with other savages...

----------------------------------------------

EVENT 3! (which ID is 21356)

Cannibal 3 had a meal.
Now there are 3 pieces of stewed missionary.

----------------------------------------------

EVENT 4! (which ID is 20944)

Great pitty! Cannibal -4 does not leave
in this tribe, he cannot eat missionary's
meat with other savages...

----------------------------------------------

EVENT 5! (which ID is 22840)

Cannibal 5 had a meal.
Now there are 2 pieces of stewed missionary.

----------------------------------------------

EVENT 6! (which ID is 13436)

Great pitty! Cannibal -6 does not leave
in this tribe, he cannot eat missionary's
meat with other savages...

----------------------------------------------

EVENT 7! (which ID is 22760)

Cannibal 7 had a meal.
Now there are 1 pieces of stewed missionary.

----------------------------------------------

Time of program working = 0.008 sec

----------------------------------------------

****

ТЕСТ 3:

Третий тест содержит в себе 1001 строчку (полностью текст теста можно просмотреть в файле «test3.txt»). Он был разработан для демонстрации факта того, что программа справляется с достаточно большим объемом данных.

.bat файл для тестирования продемонстрированных входных данных имеет название Correct_Input_test3.bat и содержит в себе текст «MP2.exe test3.txt».

Для более ознакомления с текстом и результатами третьего теста предлагается протестировать его самостоятельно.

****

ТЕСТ: НЕКОРРЕКНЫЕ ДАННЫЕ

Для того чтобы продемонстрировать поведение программы при некорректных входных данных, был разработан .bat файл «Incorrect_Input_Without_Params.bat», в котором находится лишь название .exe файла.

Результат:

![Результат1](https://sun9-31.userapi.com/impg/0ItEYC5OQKKFCQsrVGIhwkoqQhMtD6y74RRxTA/92_7ZJgryNg.jpg?size=396x299&quality=96&proxy=1&sign=2c8178a17666c33bc6013c9b881dc4d6&type=album)
