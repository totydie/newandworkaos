#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Обработчик сигнала
void signal_handler(int signum) {
    printf("Received signal %d. Resetting to default action.\n", signum);
    // Восстановление действия по умолчанию для сигнала SIGINT
    signal(SIGINT, SIG_DFL);
}

int main() {
    // Установка структуры sigaction
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // Установка обработчика сигнала SIGINT с использованием sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up sigaction");
        return 1;
    }

    printf("ждем сигнала. Ctrl+C to send SIGINT.\n");

    // 
    while (1) {
        sleep(1);
    }

    return 0;
}
