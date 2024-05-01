#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char stob(char *);

int main(int argc, char* argv[]) {
    unsigned char byte;
    char buf[8];
    int src, dest, n;

    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while ((n = read(src, buf, sizeof(char) * 8)) > 0) {
        for (; n < 8; n++) {
            buf[n] = '0';
        }

        byte = stob(buf);
        write(dest, &byte, sizeof(char) * 1);
    }

    close(src);
    close(dest);

    return 0;
}

unsigned char stob(char *bits) {
    return '\0';
}
