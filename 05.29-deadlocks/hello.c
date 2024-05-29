#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    /* This program expects to read from stdin and write to stdout -- if we
     *  wish to communicate with it, we have to trick it into using pipes
     *  instead by replacing stdin/stdout with pipes. */

    fgets(buf, sizeof(char) * 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return 0;
}
