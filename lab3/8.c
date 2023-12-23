#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
// \
внешний цикл мах значение параметра цикла (INT_MAX).\
сигнал отличен от SIGUSR1, то устанавливается стандартная реакция (SIG_DFL).\
порожденный процесс вызывает pause, ожидая получения сигнала. \
SIGUSR1 из родительского процесса, порожденный процесс выходит из режима pause и выполняет внешний цикл.\
родитель ждет завершения порожденного процесса с помощью wait и выводит статус завершения.
// выполняет внешний цикл с (INT_MAX) при получении сигнала SIGUSR1 
int i;
void child_disp(int sig) {
    i = 9998;
}
//В порожденном процессе (child_code),  функцию signal для переопределения стандартной реакции на сигнал SIGUSR1.
void child_code() {
    signal(SIGUSR1, child_disp);
    for (i = 0; i < 10000; i++) {
            printf("outer loop %d\n", i);
            for (int j = 0; j < 1000; j++)
                for (int k = 0; k < 1000; k++)
                    ;
        }
    exit(0);
}

int main() {

    int child_pid;

    if ((child_pid = fork()) == 0) {
        child_code();
    } else {
        int code;
        sleep(1);
        kill(child_pid, SIGUSR1);
        wait(&code);
        printf("wait: status %d\n", code);
    }
    return 0;
}