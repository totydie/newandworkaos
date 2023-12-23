#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSG_LEN 32

extern int errno;

typedef struct msg_ds {
    long type;
    char data[MSG_LEN + 1];
} msg_ds;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Некорректные аргументы командной строки\n");
        exit(1);
    }

    char *ptr;

    int msqid = strtol(argv[1], &ptr, 0);

    msgctl(msqid, IPC_RMID, 0);
    return 0;
}