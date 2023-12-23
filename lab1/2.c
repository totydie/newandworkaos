#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>  
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <permissions>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    mode_t permissions = strtol(argv[2], NULL, 8);

    // Создание нового файла с заданными правами доступа (только на чтение)
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    // Запись нескольких строк в файл
    const char *content = "Hello line 1.\nAnd this is line 2.";
    write(fd, content, strlen(content));

    // Закрытие файла
    close(fd);

    // Повторное открытие файла на чтение
    fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // Чтение и вывод информации на экран
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    printf("Read from file:\n%.*s\n", (int)bytesRead, buffer);

    // Закрытие файла
    close(fd);

    // Повторное открытие файла на чтение и запись
    fd = open(filename, O_RDWR);

    if (fd == -1) {
        perror("Error opening file for reading and writing");
        exit(EXIT_FAILURE);
    }

    // Проверка результатов системного вызова open
    struct stat fileStat;
    fstat(fd, &fileStat);

    printf("File permissions after reopening: %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

    // Закрытие файла
    close(fd);

    return 0;
}
// 2 test.txt и права там 664 