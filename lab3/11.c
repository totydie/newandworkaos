#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>

// Функция, реализующая синхронизацию между процессами
void synced(pid_t other_pid) {
    pid_t this_pid = getpid();
    sigset_t sigset, e_sigset;

    // Устанавливаем блокировку для сигнала SIGUSR1
    sigaddset(&sigset, SIGUSR1);
    sigemptyset(&e_sigset);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    // Если это дочерний процесс, то он ожидает сигнала от родительского процесса
    if (this_pid < other_pid) {
        printf("Child waiting for signal from parent...\n");
        sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    }

    // Бесконечный цикл с отправкой сигнала и ожиданием
    while (1) {
        printf("%d\n", this_pid);
        sleep(rand() % 5);
        kill(other_pid, SIGUSR1);
        sigsuspend(&e_sigset);
    }
}

// Обработчик сигналов
void disp(int sig) {
    if (sig == SIGUSR1) {
        // Здесь можно добавить дополнительные действия при получении SIGUSR1
        // Например, printf("Received SIGUSR1\n");
    } else {
        // Если пришел другой сигнал, то установим обработчик по умолчанию
        signal(sig, SIG_DFL);
    }
}

int main() {
    srand(time(NULL));

    // Настройка обработчика сигнала SIGUSR1
    struct sigaction sa;
    sa.sa_handler = disp;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    int parent_pid = getpid(), child_pid;

    // Создание дочернего процесса
    if ((child_pid = fork()) < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Если это дочерний процесс
        synced(parent_pid);
    } else {
        // Если это родительский процесс
        synced(child_pid);
    }

    return 0;
}
