#include <stdio.h>

/* If we cared about the command line arguments, we could take them as the
 *  parameters "argc" and "argv", but if we don't plan to use them, we should
 *  instead use "void" to indicate that we don't care about them. */
int main(void) {
    printf("Hello, world!\n");

    return 0;
}
