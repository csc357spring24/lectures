#include <stdio.h>

void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    /* Rather than telling a function *what* the arguments are, pointers allow
     *  us to tell it *where* they can be found, in order to emulate
     *  pass-by-reference behavior: */
    swap(&z, &w);

    printf("z (%p): %d\n", (void *)&z, z);
    printf("w (%p): %d\n", (void *)&w, w);

    return 0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}
