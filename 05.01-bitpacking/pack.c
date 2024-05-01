#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int src, dest, n;

    /* There are no exceptions in C; instead, system calls will set a global
     *  variable errno to indicate any errors. The standard library function
     *  perror can be used to print human-readable error messages to stderr
     *  based on that variable. */
    if ((src = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror(argv[2]);
        close(src);
        exit(EXIT_FAILURE);
    }

    /* The standard library and the system calls cannot read or write fewer
     *  than 1 byte at a time. We'll have to read in 8 "bits" at once, then
     *  pack them into a single byte: */
    while ((n = read(src, buf, sizeof(char) * 8)) > 0) {
        /* ...which means the last byte may need to be padded with 0's: */
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        write(dest, &byte, sizeof(char) * 1);
    }

    close(src);
    close(dest);

    return EXIT_SUCCESS;
}

unsigned char stob(char *bits) {
    unsigned char byte = 0, mask;

    /* Note that the string will be of the form "00100001", with the character
     *  at index 0 being the MSB of the byte we're packing. */

    for (mask = 0x80; mask > 0; mask >>= 1) {
        if (*(bits++) == '1') {
            byte = byte | mask;
        }
    }

    return byte;
}
