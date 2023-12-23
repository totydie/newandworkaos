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
        // Код, который выполнится только родительским процессом
        printf("Whhhhhat\n");
    } else {
        // Код, выполняемый только дочерним процессом
        sleep(15);
        ppid = getppid();
        printf("child: Hello from the child process!\n");
        printf("ppid=%d\n", ppid);
        exit(EXIT_SUCCESS);
    }

    // Общий код, который выполнится и родительским, и дочерним процессом
    printf("Both processes continue from here.\n");

    return 0;
}
