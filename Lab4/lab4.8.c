#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {
    const char* filename = argv[1];
    char buf[5] = {0};
    char msg[] = "second message";
    
    if (fork() != 0) {
        int fd = open(filename, O_RDONLY);
        int r;
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_len = 0;
        lock.l_start = 0;
        while(fcntl(fd, F_SETLK, &lock) == -1);
        
        do{
            r = read(fd, buf, 5);
            for (int i = 0; i < r; ++i)
            printf("%c", buf[i]);
        } while (r == 5);

        
        lock.l_type = F_UNLCK;
        while(fcntl(fd, F_SETLK, &lock) == -1);
        close(fd);
    } 
    else {
        int fd = open(filename, O_WRONLY | O_CREAT, 0666);
        int n;
        struct flock lock = {0};
        while(1){
            fcntl(fd, F_GETLK, &lock);
            if(lock.l_type == F_UNLCK) break;
        }
        n = write(fd, msg ,sizeof(msg));
            //perror("");
        printf("\nwrite bytes: %d\n", n);
    
        
        close(fd);
    }
}