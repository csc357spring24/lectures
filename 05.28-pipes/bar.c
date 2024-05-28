#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fds[2];

    /* Creating a pipe essentially creates a temporary "file" that is managed
     *  by the OS -- it's not a real file on disk, but the OS allows us to
     *  pretend that it can be accessed via file descriptors just like any
     *  other form of I/O. */

    pipe(fds);

    /* Children inherit their parents' open files, so by creating a pipe before
     *  forking a child, the child will gain access to the same pipe. */

    if (!fork()) {
        char buf[5];
        int n;

        close(fds[1]);

        while ((n = read(fds[0], buf, 4)) > 0) {
            buf[n] = '\0';
            printf("%ld read \"%s\".\n", (long)getpid(), buf);
        }

        close(fds[0]);
    }
    else {
        close(fds[0]);

        write(fds[1], "Hello, world!", 13);
        printf("%ld wrote \"Hello, world!\".\n", (long)getpid());

        /* Closing a pipe is the only way the OS will know that we no longer
         *  plan to use it -- closing the write end is not just a matter of
         *  best practice; it's the only way other processes will know that no
         *  more data will be written. */

        close(fds[1]);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
