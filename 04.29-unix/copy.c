#include <unistd.h>
#include <fcntl.h>

/* Note that a system call is not an ordinary function call. System calls have
 *  to transfer control to and from the operating system: there is additional
 *  overhead involved in a system call, and it is in our best interests to
 *  minimize the number of system calls we have to make. */
#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;

    /* The system call open does not return a file structure, it returns an
     *  integer file descriptor. This is essentially an index into a big array
     *  behind the scenes, containing all of the open files; it is the bare
     *  minimum information required to interact with an open file. */
    int src, dest;

    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while ((n = read(src, buf, sizeof(char) * SIZE)) > 0) {
        write(dest, buf, sizeof(char) * n);
    }

    close(src);
    close(dest);

    return 0;
}
