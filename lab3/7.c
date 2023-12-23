#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void child_code() {
    pause();
    //exit(0);
}
//cигнал SIGUSR2 отправляется из родительского процесса.
int main() {

    int child_pid = fork();

    if (child_pid) {
        child_code();
    } else {
        int code;
        kill(child_pid, SIGUSR2);
        wait(&code);
        printf("wait: status %d\n", code);
    }
    return 0;
}





// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <fcntl.h>
// #include <string.h>
// #include <signal.h>

// volatile sig_atomic_t terminate_flag = 0;

// void termination_handler(int signum) {
//     printf("Received termination signal. Exiting.\n");
//     exit(0);
// }

// void child_code() {
//     signal(SIGTERM, termination_handler); // Добавляем обработчик сигнала завершения

//     for (int i = 0; i < 1000; i++) {
//         printf("outer loop %d\n", i);
//         for (int j = 0; j < 1000; j++)
//             for (int k = 0; k < 1000; k++)
//                 ;

//         if (terminate_flag) {
//             printf("Termination signal received. Exiting.\n");
//             exit(0);
//         }
//     }

//     exit(0);
// }

// int main() {
//     pid_t child_pid = fork();

//     if (child_pid == 0) {
//         // Порожденный процесс
//         sleep(1); // Даем порожденному процессу время начать выполнение
//         child_code();
//     } else if (child_pid > 0) {
//         // Родительский процесс
//         sleep(2); // Даем порожденному процессу время выполнить несколько итераций
//         kill(child_pid, SIGTERM); // Отправляем сигнал завершения порожденному процессу
//         int status;
//         waitpid(child_pid, &status, 0);
        
//         // Родительский процесс ждет завершения порожденного процесса с помощью wait,
//         // и затем выводит статус завершения.
//         if (WIFEXITED(status)) {
//             printf("Child process exited with status %d\n", WEXITSTATUS(status));
//         } else {
//             printf("Child process exited abnormally\n");
//         }
//     } else {
//         perror("Fork failed");
//     }

//     return 0;
// }