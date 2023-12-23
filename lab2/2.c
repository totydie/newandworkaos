#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {
        // Родительский процесс
        printf("parent\n");
    } else if (child_pid == 0) {
        // Дочерний процесс
        printf("child\n");
    }

    return 0;
}
