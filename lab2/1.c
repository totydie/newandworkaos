#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void add_environment_variable() {
    if (putenv("MY_VARIABLE=my_value") != 0) {
        perror("putenv failed");
        exit(1);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    int status;
    char *f = argv[1];
    argv++;

    add_environment_variable(); // Добавляем новую переменную окружения

    pid = fork();
    switch(pid) {
        case -1:
            perror("fork failed");
            exit(1); 
        case 0:
            execvp(f, argv);
            exit(0);
        default:
            wait(&status);

            // Проверяем, что MY_VARIABLE была успешно добавлена в среду процесса
            const char *value = getenv("MY_VARIABLE");
            if (value) {
                printf("MY_VARIABLE=%s\n", value);
            } else {
                printf("MY_VARIABLE not found\n");
            }
            
            exit(0);
    }
}
