#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t child;

    if ((child = fork()) == 0) {

        /* By convention, the first command line argument to an executable is
         *  always the name of that executable, so the second argument to exec
         *  should match the first argument to exec. */

        execlp("grep", "grep", argv[1], argv[2], NULL);

        /* If exec succeeds, all of this code will be replaced by that of
         *  another executable, so the only way to reach this line is if the
         *  call to exec failed. */

        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        child = wait(&status);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        else {
            return EXIT_FAILURE;
        }
    }
}
