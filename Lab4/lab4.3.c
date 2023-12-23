#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
// два канала для обмена информацией между родительским и дочерним процессами.\
 Дочерний процесс читает из одного канала и пишет в другой, а родительский процесс делает обратное. 
int main() {
    int fd[2], fd_rev[2];
    pipe2(fd, O_NONBLOCK);  // Создание канала с неблокирующим режимом
    pipe(fd_rev);  // Создание второго канала

    if (fork() == 0) {  // Дочерний процесс

        close(fd[0]);  // Закрыть чтение из первого канала
        close(fd_rev[1]);  // Закрыть запись во втором канале

        int n, r;
        char buf[20] = {0};
        do {
            memset(buf, 0, 20);
            n = read(STDIN_FILENO, buf, 20);  // Чтение из стандартного входного потока
            write(fd[1], buf, n);  // Запись в первый канал
            memset(buf, 0, 20);
            r = read(fd_rev[0], buf, 20);  // Чтение из второго канала
            if (r > 0) 
                printf("Получено от родителя: %s", buf);  // Вывод полученных данных от родителя
        } while(1);
        close(fd[1]);  // Закрыть запись в первом канале
        close(fd_rev[0]);  // Закрыть чтение из второго канала

    } else {  // Родительский процесс
        close(fd[1]);  // Закрыть запись в первом канале
        close(fd_rev[0]);  // Закрыть чтение из второго канала
        int r;
        do {
            char buf[20] = {0};
            sleep(4);  // Пауза на 4 секунды
            r = read(fd[0], buf, 20);  // Чтение из первого канала
            if (r > 0) {
                printf("Получено от ребенка: %s", buf);  // Вывод полученных данных от ребенка
                write(fd_rev[1], buf, r);  // Запись во второй канал
            }
            if (r == -1) break;
        } while(1);

        close(fd[0]);  // Закрыть чтение из первого канала
        close(fd_rev[1]);  // Закрыть запись во втором канале
    }

    return 0;
}
