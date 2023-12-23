#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

void disp(int sig) {
    if (sig == SIGINT) printf("got SIGINT\n");
    else signal(sig, SIG_DFL);
}
//sigprocmask для блокировки и разблокировки SIGINT. 
//предотвращает обработку сигнала во время выполнения критической секции кода -  doing something...
int main() {
    signal(SIGINT, disp);

    sigset_t sigset;
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    //разблокировка сигнала с помощью sigprocmask 

    printf("doing something...\n");
    sleep(5);
    printf("finish doing.\n");

    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    sleep(1);
    printf("exiting\n");
    return 0;
}

//Что произойдет, если во время обработки некоторого сигнала в процесс поступит несколько однотипных заблокированных сигналов.

//сигналы будут помещены в ожидание до тех пор, пока соответствующий тип сигнала не будет разблокирован sigprocmask 