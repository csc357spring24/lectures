#include <stdio.h>

int main(void) {
    short int x;

    /* Since "x" is declared as "short", it almost certainly occupies only 16
     *  bits in memory, and the following will overflow: */

    x = 16384;
    printf("x: %d\n", x);
    x *= 2;
    printf("x: %d\n", x);

    /* Booleans are integers, where 0 is falsey and anything else is truthy,
     *  which means it is valid syntax to compare a boolean to an integer using
     *  a relational operator, but that's probably not desired. */

    x = 0;
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* This doesn't compile; local variables have block scope, and must be
     *  declared as soon as they come into scope. */
    /* int y = 1; */

    /* This introduces a new local scope: */
    {
        int y = 1;
        printf("y (outside): %d\n", y);

        {
            /* This "shadows" the "y" on line 28: */
            int y = 2;
            printf("y (inside): %d\n", y);
        }

        printf("y (outside): %d\n", y);

        /* This continues to use the "x" from the nearest enclosing scope: */
        x = 3;
        printf("x (inside): %d\n", x);

    }

    printf("x (outside): %d\n", x);

    /* This doesn't compile; there are no "y"s in the current scope: */
    /* printf("y (outside): %d\n", y); */

    return 0;
}
