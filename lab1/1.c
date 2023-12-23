#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        // Вывод сообщения об ошибке с использованием strerror
        fprintf(stderr, "Error using strerror: %s\n", strerror(errno));
        
        exit(EXIT_FAILURE);
    } else {
        printf("File opened successfully!\n");

        // Дополнительный код для работы с открытым файлом может быть добавлен здесь

        close(fd);
    }

    return 0;
}
