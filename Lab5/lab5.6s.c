#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define _GNU_SOURCE


extern int errno;

typedef struct msg {
    long type;
    char data[32];
} msg;

// void scan(long *type, char* data){
//     scanf("%ld",type);
//     scanf("%s", data);

// }
void scan(char* data){
    scanf("%s", data);

}

int main(int argc, char *argv[]) {
    
    key_t key = ftok(argv[1], 'a');
    int msqid = msgget(key, IPC_CREAT | 0666);
    printf("id q server: %d\n", msqid);

    msg req;
    msg res;

    int i = 0;

    while(1) {
        msgrcv(msqid, &req, sizeof(req), 0, 0);

        printf("Получено сообщение:\n");
        printf("%s\n", req.data);

        res.type = req.type;
        printf("Ввод ответного сообщения:\n");
        scan(&res.data);

        msgsnd(res.type, &res, sizeof(res), 0);

        printf("Сообщение отправлено\n");

    }
    return 0;
}