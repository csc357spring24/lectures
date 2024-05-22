#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "spork.h"

int main(void) {
    int status;
    pid_t child;

    if ((child = spork(5)) == 0) {
        printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());

        while (1) {
            fork();
            perror("fork");
            sleep(1);
        }
    }
    else {
        printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);
        child = wait(&status);

        if (WIFEXITED(status)) {
            printf("%ld exited status %d.\n", (long)child, WEXITSTATUS(status));
        }
        else {
            printf("%ld terminated abnormally.\n", (long)child);
        }
    }

    return 0;
}
