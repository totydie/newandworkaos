#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>


extern int errno;

typedef struct msg_ds {
    long type;
    char data[2];
} msg_ds;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Некорректные аргументы командной строки\n");
        exit(1);
    }

    char *ptr;

    int msqid = strtol(argv[1], &ptr, 0);
    long msg_type = strtol(argv[2], &ptr, 0);

    msg_ds msg = {0};
    msgrcv(msqid, &msg, sizeof(msg), msg_type, IPC_NOWAIT | MSG_NOERROR);
    for (int i = 0; i < sizeof(msg.data); ++i){
        printf("%c", msg.data[i]);
    }
    printf("\n");
    printf("%s\n", msg.data);

    return 0;
}