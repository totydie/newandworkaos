#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 

int main() {
    pid_t pid, ppid;
    gid_t gid;
    int fork_result;

    printf("before fork:\n");
    pid = getpid();
    ppid = getppid();
    gid = getgid();
    printf("pid=%d\nppid=%d\ngid=%d\n", pid, ppid, gid);

    fork_result = fork();

    if (fork_result == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    printf("after fork:\n");
    pid = getpid();
    ppid = getppid();
    gid = getgid();
    printf("pid=%d\nppid=%d\ngid=%d\n", pid, ppid, gid);

    if (fork_result) {
        int child_status;
        pid_t child_pid = waitpid(fork_result, &child_status, 0);

        if (child_pid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        printf("parent: child pid %d\n", child_pid);
        printf("parent: child status %d\n", WEXITSTATUS(child_status));
    } else {
        // Код, выполняемый дочерним процессом
        printf("child: Hello from the child process!\n");
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}
