#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
#include <sys/select.h>

int main() {
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    
    int fd1[2], fd2[2];

    pipe(fd1);  // Создание первого канала
    pipe(fd2);  // Создание второго канала

    if (fork() == 0) {  // Дочерний процесс

        close(fd1[1]);  // Закрыть запись в первом канале
        close(fd2[0]);  // Закрыть чтение из второго канала

        char buf[20] = {0};
        read(fd1[0], buf, 20);  // Чтение из первого канала
        printf("Read child from parent: %s\n", buf);
        const char* reply = "I'm child";
        write(fd2[1], reply, strlen(reply));  // Запись во второй канал

        close(fd1[0]);  // Закрыть чтение из первого канала
        close(fd2[1]);  // Закрыть запись во втором канале
        
    } else {  // Родительский процесс

        close(fd1[0]);  // Закрыть чтение из первого канала
        close(fd2[1]);  // Закрыть запись во втором канале
        const char* buf = "I'm parent";
        write(fd1[1], buf, strlen(buf));  // Запись в первый канал

        char reply[1024] = {0};
        read(fd2[0], reply, 1024);  // Чтение из второго канала
        printf("Read parent from child: %s\n", reply);

        close(fd1[1]);  // Закрыть запись в первом канале
        close(fd2[0]);  // Закрыть чтение из второго канала
        
    }

    return 0;
}
