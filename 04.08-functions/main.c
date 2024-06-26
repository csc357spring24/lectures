/* To copy the text within "stdio.h" into the current file: */
#include <stdio.h>

/* To copy the text within "add.h" into the current file: */
#include "add.h"

/* To replace the text "ONE" with the text "1", note the lack of semicolons: */
#define ONE 1

/* To redefine the "add" function as a (mostly) equivalent macro: */
#define ADD(X, Y) ((X) + (Y))

int main(void) {
    /* To apply a function that takes two ints and returns a third int: */
    printf("add(ONE, 2): %d\n", add(ONE, 2));
    printf("add(3, 4) * 2: %d\n", add(3, 4) * 2);

    /* This expands to "((3) + (4)) * 2": */
    printf("ADD(3, 4) * 2: %d\n", ADD(3, 4) * 2);

    return 0;
}
