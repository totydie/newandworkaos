#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>

#define _GNU_SOURCE
//./client_program <server_key> использ keyserv открывать вместе с lab5.6s

extern int errno;

typedef struct msg {
    long type;   // Тип сообщения
    char data[32];  // Данные сообщения
} msg;

// Функция для считывания данных с клавиатуры и записи в переменную data
void scan(char* data){
    scanf("%s", data);
}

int main(int argc, char *argv[]) {
    // Проверка корректности аргументов командной строки
    if (argc != 2) {
        printf("Некорректные аргументы командной строки\n");
        exit(1);
    }

    char *ptr;

    // Генерация ключа для серверной очереди сообщений
    key_t key_server = ftok(argv[1], 'a');
    
    // Создание или получение серверной очереди сообщений
    int msqid_server = msgget(key_server, IPC_CREAT | 0666);
    printf("id q server: %d\n", msqid_server);

    // Создание или получение клиентской очереди сообщений
    int msqid_client = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    msg req;  // Структура для запроса
    msg res;  // Структура для ответа

    int i = 0;

    while(1) {
        printf("Ввод сообщения:\n");
        
        // Заполнение структуры запроса данными, введенными с клавиатуры
        req.type = msqid_client;
        scan(req.data);
        
        // Отправка запроса в серверную очередь
        msgsnd(msqid_server, &req, sizeof(req), 0);
        
        sleep(5);  // Ожидание для демонстрации асинхронности
        
        // Получение ответа от сервера из клиентской очереди
        msgrcv(msqid_client, &res, sizeof(res), 0, 0);

        // Вывод полученного ответа
        printf("Получено сообщение: %s\n", res.data);
    }

    return 0;
}
