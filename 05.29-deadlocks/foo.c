#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int ptoc[2], ctop[2];

    /* This could theoretically be done with a single pipe, if we were careful
     *  to coordinate who read and who wrote from and to that pipe and when,
     *  but it's a lot easier to make two pipes, one for each direction. */

    pipe(ptoc);
    pipe(ctop);

    if (!fork()) {
        dup2(ptoc[0], STDIN_FILENO);
        dup2(ctop[1], STDOUT_FILENO);

        /* Once the pipes have replaced the standard I/O descriptors, we don't
         *  need any of the pipe descriptors anymore. Note that, just as the
         *  standard streams are automatically opened when a process is created,
         *  they are also automatically closed on termination. */

        close(ptoc[0]);
        close(ptoc[1]);
        close(ctop[0]);
        close(ctop[1]);

        execlp("./hello", "./hello", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else {
        char buf[81];

        close(ptoc[0]);
        close(ctop[1]);

        /* Both processes are planning to both read and write with pipes, but
         *  they can't both read first -- someone has to write first, otherwise
         *  they will be "deadlocked" waiting on the other to write. */

        write(ptoc[1], "world\n", 6);
        close(ptoc[1]);

        read(ctop[0], buf, 81);
        printf("Child printed:\n%s", buf);
        close(ctop[0]);

        wait(NULL);
    }

    return EXIT_SUCCESS;
}
