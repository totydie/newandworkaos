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
// Для передачи дескрипторов канала в порожденный процесс можно воспользоваться механизмом наследования файловых дескрипторов.
extern int errno;
extern char **environ;



int main(int argc, char** argv) {
    int fd[2];

    pipe2(fd, O_NONBLOCK);

    if (fork() == 0) {
        char fd0 = fd[0] + '0';
        setenv("fd0", &fd0, 1);
        char fd1 = fd[1] + '0';
        setenv("fd1", &fd1, 1);
        
        // for (char **it = environ; *it; it++) {
        //         printf("%s\n", *it);
        //     }
        
        
        execvp("./lab4.4_1", argv);
        

    } else {
        
        close(fd[1]);
        int r;

        do {
           
            char buf[20] = {0};
            sleep(5);
            r = read(fd[0], buf, 20);
            printf("Получено от ребенка: %s\n", buf);
            
            if (r == -1) {
                break;
                //sleep(3);
            }
            
        } while(1);

        close(fd[0]);
        
    }

    return 0;
}