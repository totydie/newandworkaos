#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s filename [filename ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = NULL;
    long max_size = 0;
    struct stat curr_stat = {0};

    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &curr_stat) == -1) {
            perror("Error getting file information");
            continue;
        }

        long curr_size = curr_stat.st_size;
        if (curr_size > max_size) {
            max_size = curr_size;
            filename = argv[i];
        }
    }

    if (filename != NULL) {
        printf("%s (size %ld bytes)\n", filename, max_size);
    } else {
        printf("All files are empty or do not exist.\n");
    }

    return 0;
}
