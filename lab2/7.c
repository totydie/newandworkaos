#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void signal_handler(int signo) {
    if (signo == SIGINT) {
        printf("Received SIGINT\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    pid_t pid, ppid, new_pgid;
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

    if (fork_result) {
        wait(NULL); // Ожидаем завершение дочернего процесса
    } 
    else {
        // Дочерний процесс
        new_pgid = getpid(); // PID дочернего процесса
        setpgrp(); // дочерний процесс в новую группу процессов
        printf("child process group id: %d\n", getpgrp()); // Выводим ID группы процессов
        pause();
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_SUCCESS);
}
