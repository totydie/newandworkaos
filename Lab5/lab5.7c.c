#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>

#define _GNU_SOURCE

extern int errno;

void scan(char* data){
    scanf("%s", data);

}
typedef struct msg {
    long type;
    int sender;
    int reciever;
    char data[32];
} msg;


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Необходимо 2 параметра");
        exit(1);
    }

    key_t key_server = ftok("keyfile1", 'a');
    int msqid_server = msgget(key_server, IPC_CREAT | 0666);
    printf("ID сервера: %d\n", msqid_server);

    int msqid_client = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    printf("ID клиента: %d\n", msqid_client);

    msg req;
    msg res;



    char *ptr;

    long own_type = strtol(argv[1], &ptr, 0);
    fprintf(stdout, "Свой тип: %ld\n", own_type);

    long another_type = strtol(argv[2], &ptr, 0);
    fprintf(stdout, "Чужой тип: %ld\n", another_type);


    req.type = own_type;
    req.sender = msqid_client;
    req.reciever = msqid_server;
    msgsnd(msqid_server, &req, sizeof(req), 0);
    
    // req.type = own_type;
    // msgsnd(msqid_server, &req, sizeof(req), 0);

    req.reciever = 0;

    while(1) {
        msgrcv(msqid_client, &res, sizeof(res), 0, 0);
        printf("Ввод сообщения:\n");
        req.type = another_type;
        req.sender = msqid_client;
        scan(&req.data);
        
        msgsnd(msqid_server, &req, sizeof(req), 0);
        sleep(1);
        
        printf("Получено сообщение: %s \n", res.data);
        printf("\n");
        

    }

    return 0;
}