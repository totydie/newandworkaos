#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

const int BUF_SIZE = 1024;

int cp(int in, int out){
    char buf[BUF_SIZE];
    int n_read;
	
	while ((n_read = read(in, buf, BUF_SIZE)) > 0){
		if ((write(out, buf, n_read)) != n_read)
			return -1;
	}
	if (n_read == -1)
		return -1;

    return 0;
}

int main (int argc, char** argv){
    const char* inPath  = (argc > 1) ? argv[1] : NULL;
    const char* outPath = (argc > 2) ? argv[2] : NULL;
    int d_in;
    int d_out;
	

    if (inPath){
        if ((d_in = open(inPath,O_RDONLY)) == -1){
            perror ("Failed to open input file");
            return 1;
        }
    }
    else
        d_in = STDIN_FILENO;
	
    if (outPath){
        d_out = open(outPath, O_CREAT|O_TRUNC|O_WRONLY, 0666);
        if(d_out == -1){
            perror ("Failed to open output file");
            return 1;
        }
    }
    else
        d_out = STDOUT_FILENO;
	
    if (cp(d_in, d_out) == -1)
        perror("Failed to perform copy");
	else {
		char message[] = "Successfull copy\n";
			write(STDOUT_FILENO, message, sizeof(message));
	}
    if (close(d_in) == -1)
        perror("Failed to close input file");
    if (close(d_out) == -1)
        perror("Failed to close output file");
    return 0;
}