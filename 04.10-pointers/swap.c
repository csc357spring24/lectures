#include <stdio.h>

void swap(int *, int *);

int main(void) {
    int z = 1, w = 2;

    /* Pointers allow us to tell a function *where* to find a value, rather
     *  than *what* that value is, so that the function has access to the same
     *  values that we do: */
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
