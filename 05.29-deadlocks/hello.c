#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[16];

    /* This program always reads from stdin and writes to stdout -- if we want
     *  to communicate with it while it is running, we have to trick it into
     *  using a pipe instead of the standard streams. */

    fgets(buf, sizeof(char) * 16, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("Hello, %s!\n", buf);

    return 0;
}
