#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int ptoc[2], ctop[2];

    /* This could theoretically be done with a single pipe, if we were careful
     *  about who reads and who writes and when, but it will be a lot easier to
     *  make two pipes: one for each direction. */

    pipe(ptoc);
    pipe(ctop);

    if (!fork()) {
        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* Once the standard I/O descriptors have been replaced, we no longer
         *  need the original pipe descriptors. Note that the standard I/O
         *  descriptors will be automatically closed on termination, just as
         *  they were automatically opened on creation. */

        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./hello", "./hello", NULL);
        perror("exec");
        exit(EXIT_SUCCESS);
    }
    else {
        char buf[81];

        close(ptoc[0]);
        close(ctop[1]);

        /* Both processes plan to read and write from and to pipes, but they
         *  can't both read first. Someone has to write first, otherwise they
         *  will be "deadlocked" waiting for the other process to make
         *  something happen. */

        write(ptoc[1], "world\n", 6);
        close(ptoc[1]);

        read(ctop[0], buf, 81);
        close(ctop[0]);

        printf("Child printed:\n%s", buf);

        wait(NULL);
    }

    return EXIT_SUCCESS;
}
