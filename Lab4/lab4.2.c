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
#include <errno.h>
//родительский процесс читает из канала в цикле, пока не встретится конец файла. 
extern int errno;

int main() {
    int fd[2];
    pipe2(fd, O_NONBLOCK);  // Создание канала с неблокирующим режимом

    if (fork() == 0) {  // Дочерний процесс
        close(fd[0]);  // Закрыть чтение из канала
        int n;
        while(1) {
            char buf[20] = {0};
            n = read(STDIN_FILENO, buf, 20);  // Чтение из стандартного входного потока
            write(fd[1], buf, n);  // Запись в канал
        }
        close(fd[1]);  // Закрыть запись в канале

    } else {  // Родительский процесс
        close(fd[1]);  // Закрыть запись в канале
        int r;
        do {
            char buf[20] = {0};
            sleep(5);  // Пауза на 5 секунд

            r = read(fd[0], buf, 20);  // Чтение из канала
            printf("Read parent from child: %s\n", buf);

            if (r == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue;  // Продолжить цикл, если канал пустой
                } else {
                    break;  // Выход из цикла в случае ошибки чтения
                }
            }

        } while(1);
        close(fd[0]);  // Закрыть чтение из канала
    }

    return 0;
}
