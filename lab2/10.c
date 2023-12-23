#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <executable> [arguments...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fr = fork();

    if (fr == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (fr) {
        printf("Parent process\n");
        printf("Parameters:\n");
        for (int i = 1; i < argc; i++) {
            printf("  %s\n", argv[i]);
        }

        printf("Environment:\n");
        for (char **it = envp; *it; it++) {
            printf("  %s\n", *it);
        }

        int status;
        waitpid(fr, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process exited abnormally\n");
        }

    } else {
        execvp(argv[1], argv + 1);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
