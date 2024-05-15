#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int status = EXIT_FAILURE, tmp, i;
    pid_t child;

    for (i = 2; i < argc; i++) {

        /* We call fork once, but it returns twice: both to the current
         *  now-parent process and to the child. There is no guarantee
         *  as to which process will be scheduled on the CPU first; if
         *  there is anything we wish the parent to do before the child,
         *  then those things should be done before calling fork. */

        if ((child = fork()) == 0) {
            printf("%ld is the child of %ld.\n", (long)getpid(), (long)getppid());
            status = fsearch(argv[i], argv[1]);

            /* Now that the call to fork is inside a loop, we MUST ensure that
             *  the child exits rather than going around again and making
             *  children of its own... */

            printf("%ld is exiting with status %d.\n", (long)getpid(), status);
            exit(status);
        }
        else {
            printf("%ld is the parent of %ld.\n", (long)getpid(), (long)child);

            /* We do eventually need to wait for this child, but we can't do
             *  that here, otherwise the next child would not be able to start
             *  until after this child finishes, which would defeat the purpose
             *  of doing this with multiple children. */
        }
    }

    for (i = 2; i < argc; i++) {
        child = wait(&tmp);

        if (WIFEXITED(tmp)) {
            printf("%ld exited with status %d.\n", (long)child, WEXITSTATUS(tmp));

            if (WEXITSTATUS(tmp) == EXIT_SUCCESS) {
                status = EXIT_SUCCESS;
            }
        }
        else {
            printf("%ld terminated abnormally.\n", (long)child);
        }
    }

    return status;
}

/* fsearch: Prints occurrences of a string in a file. */
int fsearch(char *fname, char *str) {
    int status = EXIT_FAILURE;
    char buf[LINELEN];
    FILE *file = fopen(fname, "r");

    while (fgets(buf, LINELEN, file) != NULL) {
        if (strstr(buf, str) != NULL) {
            printf("%s: %s", fname, buf);
            status = EXIT_SUCCESS;
        }
    }

    fclose(file);
    return status;
}
