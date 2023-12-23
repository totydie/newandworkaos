#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void child_code() {
    for (int i = 0; i < 1000; i++) {
        printf("outer loop %d\n", i);
        for (int j = 0; j < 1000; j++)
            for (int k = 0; k < 1000; k++)
                ;
    }
    //может добавить ноликов))
    exit(0);
}

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Порожденный процесс
        child_code();
    } else if (child_pid > 0) {
        // Родительский процесс
        int status;
        waitpid(child_pid, &status, 0);
        //Родительский процесс ждет завершения порожденного процесса\
        с помощью wait, и затем выводит статус завершения.
        // WIFEXITED возвращает истинное значение, если процесс завершился нормально
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process exited abnormally\n");
        }
    } else {
        perror("Fork failed");
    }

    return 0;
}
