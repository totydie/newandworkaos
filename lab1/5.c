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

    int choice;
    do {
        printf("Choose action:\n");
        printf("1 - Write\n");
        printf("2 - Read\n");
        printf("3 - Seek\n");
        printf("* - Exit\n");

        // Ввод выбора пользователя
        scanf("%d", &choice);

        // Обработка выбора пользователя
        switch (choice) {
            case 1:
                // Запись строки в файл
                const char *content = "Hello, this is a file for testing.";
                write(fd, content, strlen(content));
                break;
            case 2:
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
                break;
            case 3:
                // Ваш код для операции seek
                break;
            case '*':
                // Код для выхода из цикла
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != '*');

    // Закрытие файла
    close(fd);

    return 0;
}
