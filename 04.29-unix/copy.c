#include <unistd.h>
#include <fcntl.h>

/* Increasing the size of the buffer does not reduce the total bytes read or
 *  written, but it does reduce the total system calls needed to read or write
 *  all of those bytes. A system call is more expensive than an ordinary
 *  function call -- there is additional overhead associated with transferring
 *  control to and from the OS, and it is in our best interests to limit the
 *  total number of system calls. */
#define SIZE 4096

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    
    /* The system call open returns an integer file descriptor rather than a
     *  pointer to a FILE structure -- this is the bare minimum information
     *  needed to interact with an open file. */
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
