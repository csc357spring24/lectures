#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELEN 81

int fsearch(char *, char *);

int main(int argc, char *argv[]) {
    int status = EXIT_FAILURE, child, i, tmp;

    for (i = 2; i < argc; i++) {

        /* We call fork once, and it returns twice: it returns 0 to the child
         *  and the child's PID to the parent -- note that there is no guarantee
         *  as to which process will be scheduled first on the CPU, so if there is
         *  anything we want the parent to do before the child, it should be done
         *  before calling fork. */

        if ((child = fork()) == 0) {
            printf("Process %ld is the child of %ld.\n", (long)getpid(), (long)getppid());
            status = fsearch(argv[i], argv[1]);

            /* With the call to fork being inside a loop, we MUST ensure that
             *  the child does not go around for another iteration; we don't
             *  want the child to fork off any children of its own... */

            printf("%ld is exiting with status %d.\n", (long)getpid(), status);
            exit(status);
        }
        else {
            printf("Process %ld is the parent of %ld.\n", (long)getpid(), (long)child);

            /* Do nothing -- we do eventually have to wait for our children,
             *  but if we do that here, the second child will not be able to
             *  start until after the first child finishes, which defeats the
             *  purpose of doing this with multiple children. */
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
            printf("%ld exited abnormally.\n", (long)child);
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
