#include <stdio.h>

int main(void) {
    short int x;

    x = 16384;
    printf("x: %d\n", x);
    x *= 2;
    printf("x: %d\n", x);

    /* Booleans are integers, where 0 is falsey and all else is truthy, which
     *  means it is syntactically valid to compare booleans to integers using
     *  relational operators, but that's probably not desired behavior. */

    x = 0;
    printf("-1 < x < 1: %d\n", -1 < x < 1);
    printf("-1 < x && x < 1: %d\n", -1 < x && x < 1);

    /* This doesn't compile in ANSI C, where locals must be declared as soon
     *  as they come into scope:
     * int y = 1; */

    /* This introduces a new local scope... */
    {
        /* ...so this is a valid place to declare a new local: */
        int y = 1;
        printf("y (inside): %d\n", y);

        {
            /* This "shadows" the "x" from the enclosing scope: */
            int x = 3;
            printf("x (ininside): %d\n", x);
        }

        /* This uses the existing "x" from the nearest enclosing scope: */
        x = 2;
        printf("x (inside): %d\n", x);
    }

    /* This doesn't compile; there is no "y" current in scope:
     * printf("y (outside): %d\n", y); */
    printf("x (outside): %d\n", x);

    return 0;
}
