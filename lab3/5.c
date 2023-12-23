#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void child_code() {
    for (int i = 0; i < 10000; i++) {
        printf("outer loop %d\n", i);
        for (int j = 0; j < 1000; j++)
            for (int k = 0; k < 1000; k++)
                ;
    }
    exit(0);
}

int main() {

    int child_pid = fork();
//child_code не обрабатывает этот сигнал,\'_'/, просто продолжат выполнение своих циклов.
    if (!child_pid) {
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