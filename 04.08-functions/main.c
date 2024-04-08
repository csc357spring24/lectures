/* To copy-paste the contents of "stdio.h" into the current source file: */
#include <stdio.h>

/* To copy-paste the contents of "add.h" into the current source file: */
#include "add.h"

/* To replace every instance of "ONE" with "1", note the absence of the
 *  trailing semicolon: */
#define ONE 1

/* To redefine the "add" function as a (mostly) equivalent macro: */
#define ADD(X, Y) ((X) + (Y))

int main(void) {
    /* This does not compile; it expands to "1 = 2", which is nonsensical: */
    /* ONE = 2; */

    printf("add(ONE, 2): %d\n", add(ONE, 2));
    printf("add(3, 4): %d\n", add(3, 4));

    /* This expands to "((3) + (4))": */
    printf("ADD(3, 4): %d\n", ADD(3, 4));

    return 0;
}
