#include <stdio.h>

/* Standard library functions can't avoid making system calls, but they provide
 *  additional commonly desired functionality: for example, they maintain a
 *  buffer behind the scenes to limit the number of system calls. If we read
 *  16 bytes, fread will likely read 4096, and stash the remainder in a buffer
 *  so that they're already read when we ask for them in the future. */
#define SIZE 16

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int n;
    FILE *src, *dest;

    src = fopen(argv[1], "r");
    dest = fopen(argv[2], "w");

    while ((n = fread(buf, sizeof(char), SIZE, src)) > 0) {
        fwrite(buf, sizeof(char), n, dest);
    }

    fclose(src);
    fclose(dest);

    return 0;
}
