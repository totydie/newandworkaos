#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


// argv[1] - filename, argv[2] - permissions
int main (int argc, char** argv){
	int file;
	int write_res;
	char buf[256];
	int readnum;
	int permissions = strtol("666", NULL, 8);
    if ((file = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, permissions))  == -1)
        perror ("Failed to create file");
    else{
        char str[] = "default line in my file txt \n";
		write_res = write(file, str, sizeof(str)*sizeof(char));
        if (write_res == -1)
            perror("Write failure");
		
		// read from begin
		if (lseek (file, 0, SEEK_SET) == -1)
			perror("Seek fail");

		readnum = read(file, buf, sizeof(buf));
        if (readnum == -1)
			perror ("Read from file filed");
        if (write(STDOUT_FILENO, buf, readnum) == -1)
			perror ("Failed to print");
		
		// read from begin+4
		if (lseek (file, 4, SEEK_SET) == -1)
			perror("Seek fail");
		readnum = read(file, buf, sizeof(buf));
        if (readnum == -1)
			perror ("Read from file filed");
        if (write(STDOUT_FILENO, buf, readnum) == -1)
			perror ("Failed to print");
		
		// read from end - 4
		if (lseek (file, -4, SEEK_END) == -1)
			perror("Seek fail");
		readnum = read(file, buf, sizeof(buf));
        if (readnum == -1)
			perror ("Read from file filed");
        if (write(STDOUT_FILENO, buf, readnum) == -1)
			perror ("Failed to print");
		
		
		
		
		char mssg[] = " razrejenniy file \n\n";
		if (lseek (file, 1024*1024, SEEK_END) == -1)
			perror("Seek fail");
		if (write(file, "\nhello\n", sizeof("\nhello\n")) == -1)
			perror ("Failed to print");
		
		
		
		
        if (close(file) == -1)
            perror("Failed to close file");
		else{
			char message[] = "Successfull close";
			write(STDOUT_FILENO, message, sizeof(message));
			write(STDOUT_FILENO, "\n", 1);
		}
    }
    
	
	
    return 0;
}