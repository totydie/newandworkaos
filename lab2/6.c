#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 

void signal_handler(int signo) {
    if (signo == SIGINT) {
        printf("Received SIGINT\n");
    }
}

int main() {
    pid_t pid, ppid;
    gid_t gid;
    int fork_result;

    signal(SIGINT, signal_handler);

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

    // Оба процесса ожидают сигнала
    pause();

    exit(EXIT_SUCCESS);
}
