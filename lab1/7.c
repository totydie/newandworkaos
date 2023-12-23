#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int errno;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat statbuf = {0};

    if (stat(argv[1], &statbuf) == -1) {
        perror("Error calling stat");
        exit(EXIT_FAILURE);
    }

    printf("ID of device containing file: %lu\n", statbuf.st_dev);
    printf("Inode: %lu\n", statbuf.st_ino);

    // Output file type
    mode_t fileType = statbuf.st_mode & S_IFMT;
    if (S_ISREG(fileType)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(fileType)) {
        printf("File type: Directory\n");
    } else if (S_ISLNK(fileType)) {
        printf("File type: Symbolic link\n");
    } else {
        printf("File type: Other type of file\n");
    }

    printf("Number of hard links: %lu\n", statbuf.st_nlink);
    printf("Owner user ID: %u\n", statbuf.st_uid);
    printf("Owner group ID: %u\n", statbuf.st_gid);
    printf("Device ID (if special file): %lu\n", statbuf.st_rdev);
    printf("Total size, bytes: %lld\n", (long long)statbuf.st_size);
    printf("I/O block size: %lu\n", statbuf.st_blksize);
    printf("Blocks: %lu\n", statbuf.st_blocks);
    printf("Time of last access: %lld\n", (long long)statbuf.st_atim.tv_sec);
    printf("Time of last modification: %lld\n", (long long)statbuf.st_mtim.tv_sec);
    printf("Time of last status change: %lld\n", (long long)statbuf.st_ctim.tv_sec);

    return 0;
}
