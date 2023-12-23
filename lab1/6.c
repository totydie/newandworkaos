#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];

    // Создание нового файла с правами на чтение и запись
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    // Запись строки в начало файла
    const char *content = "Hello, this is a file for testing.";
    write(fd, content, strlen(content));

    // Позиционирование в конец файла и добавление строки (разреженное добавление)
    lseek(fd, 1024 * 1024, SEEK_SET);  // Перемещаем указатель на 1 МБайт
    write(fd, "This is a sparse addition.", strlen("This is a sparse addition."));

    // Позиционирование в начало файла
    lseek(fd, 0, SEEK_SET);

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

    return 0;
}
