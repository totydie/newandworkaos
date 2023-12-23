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
    printf("after fork:\n");
    pid = getpid();
    ppid = getppid();
    gid = getgid();
    printf("pid=%d\nppid=%d\ngid=%d\n", pid, ppid, gid);

    if (fork_result) {
        // Родительский процесс
        printf("Parent process continues without waiting.\n");
    } else {
        // Дочерний процесс
        sleep(15);
        printf("Child process exits.\n");
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}
