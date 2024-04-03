#include <stdio.h>

/* If we planned to use the command line arguments, we could take them as
 *  "argc" and "argv", the parameters of "main". If we don't plan to use them,
 *  we should declare the parameters as "void" instead so that the compiler
 *  knows we didn't just forget about them. */
int main(void) {
    printf("Hello, world!\n");

    return 0;
}
