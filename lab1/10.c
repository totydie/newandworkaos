#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Error getting file information");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(st.st_mode)) {
        fprintf(stderr, "Error: %s is a directory\n", argv[1]);
        close(fd);
        exit(EXIT_FAILURE);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);

    if (file_size == -1) {
        perror("Error getting file size");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, -1, SEEK_END) == -1) {
        perror("Error seeking to end of file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    for (off_t offset = file_size - 1; offset >= 0; --offset) {
        char letter;
        if (read(fd, &letter, 1) == -1) {
            perror("Error reading file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        putchar(letter);
        if (lseek(fd, -2, SEEK_CUR) == -1 && offset > 0) {
            perror("Error seeking backward");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    printf("\n");
    close(fd);
    return 0;
}
