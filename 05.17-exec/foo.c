#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t child;

    if ((child = fork()) == 0) {

        /* Note that, by convention, the first command line argument to an
         *  executable is the name of the executable, thus, both the first and
         *  second arguments to exec are "grep": */

        execlp("grep", "grep", argv[1], argv[2], NULL);

        /* Since a successful call to exec replaces the current executable,
         *  it never returns. The only way to get to this line is if the call
         *  to exec failed. */

        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        child = wait(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            return EXIT_SUCCESS;
        }
        else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
