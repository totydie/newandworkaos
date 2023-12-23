# newandworkaos 4 и 5 переписаные 
Лабораторная работа 1. Файлы и устройства ввода/вывода
Задание
1. Написать программу, которая выполняет некоторый системный вызов, например open, и затем выводит возвращаемую ошибку. Использовать в программе разные способы вывода сообщения об ошибке: вывод значения errno, вывод соответствующего сообщения из системного массива сообщений об ошибках sys_errlist[], вызов библиотечной функции perror.
2. Создать новый файл с правом только на чтение (имя файла и права доступа ввести из командной строки), записать в него несколько строк, закрыть. Повторно открыть данный файл на чтение, прочитать из него информацию и вывести ее на экран, закрыть. Еще раз открыть этот же файл на чтение и запись, проверить результат системного вызова open. Объяснить полученные результаты.
3. Повторно выполнить программу п. 2 с теми же исходными данными; проверить результаты выполнения каждого системного вызова. Объяснить полученные результаты.
4. Используя программу п. 2, создать новый файл с правами на чтение и запись; выполнить любые операции с файлом (чтение и/или запись), используя разные способы позиционирования. Объяснить полученные результаты.
5. Повторно выполнить программу п. 4; проверить результаты выполнения каждого системного вызова. Объяснить полученные результаты.
6. Модифицировать программу п. 4 для создания разреженного файла.
7. Написать программу для получения справочной информации о файлах с помощью системного вызова stat. Имя файла передается в программу из командной строки. Получить справочную информацию для различных типов файлов (обычный файл, каталог, специальные байт- и блок-ориентированные файлы).
8. Написать программу копирования одного файла в другой. Имена файлов задаются в командной строке (первый аргумент - исходный файл, второй - результирующий). Если аргументы командной строки отсутствуют, использовать стандартный ввод и стандартный вывод. Копирование файлов выполнить с помощью функции.
9. Изменить программу п. 8 таким образом, чтобы функция копирования 
использовала стандартные ввод и вывод, а вызывающая программа переназначала стандартные ввод и вывод на указанные в аргументах командной строки файлы.
10. Написать программу, которая выводит на экран содержимое файла в обратном порядке: сначала выводится последний символ файла, затем предпоследний и так далее до первого. Использовать lseek и read.
11. Написать программу, которая определяет, какой файл из перечисленных в командной строке имеет наибольшую длину. Вывести длину файла в байтах.


Лабораторная работа 2. Управление процессами
Задание
1. Написать программу, которая добавляет новые строки в среду процесса.
2. Кто выполняется первым после fork: отец или сын? Написать программу, которую можно использовать для проверки данной ситуации.
3. Написать программу, в которой процесс порождает новый и позволяет порожденному процессу завершиться. Оба процесса должны выводить свои идентификаторы (процесса, родительского процесса, группы процессов). Проверить идентификатор и статус завершения порожденного процесса. Выполнить данную программу и посмотреть ее результаты.
4. Изменить программу п. 3 так, чтобы родительский процесс завершился раньше порожденного. Какой процесс становится родительским для порожденного после того, как исходный родительский процесс завершился?
5. Изменить программу п. 3 так, чтобы родительский процесс выполнялся, не ожидая завершения порожденного процесса. Что произойдет с порожденным процессом, когда он завершится? Как убить зомби?
6. Изменить программу п. 3 так, чтобы оба процесса выполняли системный вызов pause после вывода идентификаторов. Запустить программу в фоновом режиме и посмотрите (с помощью ps), какие процессы существуют для данного пользователя. Выполнить kill -9 pid для родительского процесса. Что произойдет с порожденным? После очистки текущего сеанса, вновь выполнить программу, но уже в интерактивном режиме. Нажать на терминале клавишу CTRL-C. Что произойдет с родительским и порожденным процессами? Можно ли получить такой же результат, если нажать клавишу прерывания после того, как родительский процесс завершится?
7. Модифицировать программу, включив в нее setpgrp в порожденный процесс до того, как он будет выполнять pause. Повлияет ли на порожденный процесс нажатие клавиши прерывания в тот момент, когда родительский процесс "спит"? Будет ли показан порожденный процесс в выводе команды ps?
8. Открыть файл (достаточно большого размера), доступный для чтения. Имя файла передается из командной строки. После открытия файла создать параллельный процесс с помощью только fork. В обоих процессах создать свои файлы для записи, читать информацию из общего файла и копировать ее в собственные выходные файлы (не на экран). Вывести на экран содержимое полученных файлов из порожденного процесса по окончании записи в файл и из родительского процесса, дождавшись завершения порожденного процесса. Посмотреть, что изменится, если читаемую процессами информацию сразу выводить на экран.
9. Выполнить п. 8 при условии, что общий файл для чтения открывается в каждом из порожденных процессов.
10. Создать (с помощью связки fork - exec) параллельный процесс. Имя исполняемого файла для exec передается с помощью аргумента командной строки. Передать в порожденный процесс некоторую информацию через список параметров (список аргументов в функции main). Каждый процесс (и родительский, и порожденный) должен вывести на экран список переданных ему аргументов и свое окружение.
11. Выполнить из программы на Си какую-либо команду Shell (cp или ls): с помощью вызовов fork-exec, с помощью библиотечной функции system. Необходимые для команды данные передать через аргументы командной строки.

Лабораторная работа 3. Сигналы
Задание
1. Изменить реакцию процесса на некоторый сигнал при помощи signal. В функции обработчике переустановить реакцию на сигнал на значение по умолчанию. Запустить программу и объяснить наблюдаемый результат.
2. Модифицировать программу п.1 так, чтобы вместо signal использовать sigaction.
3. Написать программу, исключающую появление зомби для завершающихся порожденных процессов.
4. Создать длительный параллельный процесс (в порожденном процессе выполнять вложенные циклы, каждый на 100 или больше итераций, и выводить на экран номер итерации для внешнего цикла). Дождаться нормального завершения порожденного процесса. Посмотреть, какой статус будет передан в родительский процесс.
5. Из родительского процесса послать в порожденный процесс сигнал (SIGUSR1). Посмотреть, какой статус будет передан в родительский процесс в этом случае. Сколько итераций выполнится в порожденном процессе?
6. Повторить выполнение п. 5 задания, изменив сигнал, посылаемый в порожденный процесс. Что изменится?
7. Повторить выполнение предыдущих пунктов задания, используя в порожденном процессе вместо вложенных циклов системный вызов pause. Что изменится? Как завершить процесс в случае выполнения с pause п. 4?
8. Включить в порожденный процесс системный вызов signal, переопределяющий стандартную реакцию на сигнал (для внешнего цикла установить в функции максимальное значение параметра цикла). Что изменится?
9. Включить в порожденный процесс вместо системного вызова kill системный вызов alarm с перехватом и без перехвата сигнала. Что изменится?
10. Написать программу, иллюстрирующую способ блокирования дополнительных сигналов на время работы обработчика сигнала. Что произойдет, если во время обработки некоторого сигнала в процесс поступит несколько однотипных заблокированных сигналов.
11. Написать программу, позволяющую использовать sigaction для реализации примера синхронизации процессов. Выполнить эту программу и объяснить ее поведение. Использовать sigsuspend и sigprocmask.

Лабораторная работа 4. Взаимодействие процессов с использованием средств 
файловой системы
Задание
1. Создать параллельный процесс, используя только fork. Организовать обмен информацией между процессами через каналы. Предусмотреть однонаправленную и двунаправленную связь. При создании двунаправленной связи исключить возможность появления «смертельных объятий».
2. Модифицировать программу п. 1 таким образом, чтобы родительский процесс читал из канала в цикле, пока не встретится конец файла (порожденный процесс может записывать в канал информацию, читаемую им из стандартного входного потока). Как избежать бесконечного ожидания родительским процессом чтения из пустого канала?
3. Модифицировать программу п. 2 таким образом, чтобы процессы реализовали двунаправленную связь (диалог).
4. Повторить п. 2, создавая параллельные процессы с помощью связки fork - exec. Как передать дескрипторы канала в порожденный процесс?
5. С помощью системных вызовов pipe и dup реализовать конвейер: who | wc -l.
6. Создать именованный канал (любым способом). Убедиться, что канал создан. Рассмотреть особенности работы с именованным каналом (открыть файл с установленным и не установленным флагом O_NDELAY). Использовать его для обмена информацией с процессом, созданным другим пользователем (своим соседом).
7. Создать два параллельных процесса, в каждом из которых осуществляется работа с одним и тем же файлом. Каждый процесс открывает файл (имя файла передается через список аргументов командной строки). Один процесс пишет в файл, другой - читает из него. Что произойдет без включения блокировок?
8. Добавить в один из процессов использование слабой блокировки. Что 
произойдет?
9. Добавить использование слабой блокировки во второй. Что изменится?
10. Создать два параллельных процесса, разделяющие ввод с клавиатуры и вывод на экран. Что получится при исполнении этих процессов?
11. Повторить выполнение п. 10, включив в процессы для синхронизации работы с терминалом использование режима слабой блокировки. Как изменится поведение процессов?


Лабораторная работа 5. Очереди сообщений
Задание
1. Создать очередь сообщений или получить доступ к уже существующей очереди. Вывести на экран статистическую информацию об очереди сообщений. Поместить несколько сообщений различных типов в очередь.
2. Написать программу, позволяющую читать сообщения из очереди и выводить их на экран. Идентификатор очереди и тип сообщения передается через аргументы командной строки.
3. Модифицировать программу п. 2, позволив ей избежать ожидания в случае отсутствия в очереди сообщений данного типа.
4. Модифицировать программу п. 2, позволив ей принимать первые несколько байтов сообщений произвольных размеров.
5. Написать программу, позволяющую удалять очереди сообщений по идентификатору. Обработать возможные ошибочные ситуации.
6. Написать программы для работы с очередями сообщений в соответствии с моделью клиент-сервер: каждый процесс использует собственную очередь сообщений. Процесс-сервер читает запросы из своей очереди сообщений и посылает ответ процессам-клиентам в их очереди. Процессы-клиенты читают ответ и выводят его в выходной поток. Процессы-клиенты должны передавать процессу-серверу информацию о своих очередях сообщений (куда записывать ответ).
7. Осуществить при помощи программ п. 6. обмен сообщениями между несколькими пользователями, при условии, что каждому пользователю предназначены сообщения любого или определенного типа (по договоренности). Будут ли примеры с очередями сообщений "приводить себя в порядок"? Что произойдет, если прервать процесс-сервер с помощью клавиши CTRL-C?
8. Модифицировать программы п. 6 так, чтобы они завершались корректно и в случае прерывания по CTRL-C.
9. Модифицировать программы п. 6 так, чтобы использовались две очереди: одна для запросов к серверу и одна для всех ответов от сервера к любому клиенту.
10. Еще раз модифицировать эти программы так, чтобы использовалась только одна очередь сообщений и для запросов к серверу, и для всех ответов.
11. Написать программу, иллюстрирующую возможность синхронизации процессов при помощи очередей сообщений.



