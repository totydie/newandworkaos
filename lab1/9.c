#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

const int BUF_SIZE = 1024;

int cp(){
    char buf[BUF_SIZE];
    int n_read;
	
	while ((n_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0){
		if ((write(STDOUT_FILENO, buf, n_read)) != n_read)
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
	
   
	
	
	// change stdin and stdout
	int d_dup_in;
	int d_dup_out;
	int d_out_backup = dup(1);
	
	if (d_out_backup == 1) perror ("Failed to backup stdout");
	
	if (close(0) == -1)
        perror("Failed to close standart input file");
	if ((d_dup_in = dup(d_in)) == -1)
		 perror("Failed to dup standart input file");
	
	
	if (close(1) == -1)
        perror("Failed to close standart output file");
	if ((d_dup_out = dup(d_out)) == -1)
		 perror("Failed to dup standart output file");
	
	
	int cp_res = cp();
	if ( cp_res== -1)
        perror("Failed to perform copy");
	/*else {
		char message[] = "Successfull copy\n";
			write(STDOUT_FILENO, message, sizeof(message));
	}*/
	
	
	// return stdout back to normal
	if (close(1) == -1)
        perror("Failed to close changed output file");
	if ((d_dup_out = dup2(d_out_backup, STDOUT_FILENO)) == -1)
		 perror("Failed to restore stdout");
	 
	 
    if (close(d_in) == -1)
        perror("Failed to close input file");
    if (close(d_out) == -1)
        perror("Failed to close output file");
	
	
	if (cp_res != -1){
		char message[] = "Successfull copy\n";
			write(STDOUT_FILENO, message, sizeof(message));
	}
    return 0;
}