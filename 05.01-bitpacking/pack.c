#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int src, dest, n;

    /* If these system calls fail, there are no exceptions in C, so they will
     *  instead set the global variable errno to indicate the reason for the
     *  failure. The standard library function perror can then be used to print
     *  a human-readable error message to stderr. */
    if ((src = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        perror(argv[2]);
        close(src);
        exit(EXIT_FAILURE);
    }

    /* It is not possible to write less than a byte to a file, so if we want to
     *  write individual bits, we have to do it 8 bits at a time... */
    while ((n = read(src, buf, sizeof(char) * 8)) > 0) {
        /* ...if there aren't 8 more bits to be written, we have to pad them
         *  out with 0's. */
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        write(dest, &byte, sizeof(char) * 1);
    }

    close(src);
    close(dest);

    /* EXIT_SUCCESS is almost certainly 0, and EXIT_FAILURE is almost certainly
     *  1, but for portability we should use the macros instead of hardcoding
     *  the integers. */
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
