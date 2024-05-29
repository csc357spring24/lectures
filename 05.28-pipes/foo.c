#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fds[2];

    /* Create a "file" managed by the OS, where fds[0] is the "read end", and
     *  fds[1] is the "write end": */
    pipe(fds);

    /* Children inherit their parents' open files, so by making the pipe before
     *  forking a child, both the parent and the child have access to it. */

    if (!fork()) {
        char buf[5];
        int n;

        close(fds[1]);

        /* Note that "read" is a blocking call -- if the OS decides to run the
         *  child process first, such that the parent has not yet written data
         *  to the pipe, the child process will be "blocked" until there is
         *  data to be read. */

        while ((n = read(fds[0], buf, 4)) > 0) {
            buf[n] = '\0';
            printf("%ld read \"%s\"\n", (long)getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        /* The parent never needs the read end, but it cannot close it until
         *  after the child has inherited it, since the child does need it. */

        close(fds[0]);

        write(fds[1], "Hello, world!", 13);
        printf("%ld wrote \"Hello, world!\"\n", (long)getpid());

        /* Closing our open files is no longer just a matter of cleaning up
         *  after ourselves; closing the write end of the pipe is how the OS
         *  (and any processes reading) know there is no more data coming. */

        close(fds[1]);

        wait(NULL);
    }

    return EXIT_SUCCESS;
}
