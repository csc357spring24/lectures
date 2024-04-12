#include <stdio.h>

void swap(int *, int *);
void reverse(int[], int);

int main(void) {
    int arr[4] = {1, 2, 3, 4};

    /* To pass an array as an argument -- note that the length must be passed
     *  separately if desired: */
    reverse(arr, 4);

    /* ...since an array is an address, it is always passed and returned as a
     *  pointer. The elements are never copied on the stack. If an array is
     *  passed as argument, modifications to that array will affect the
     *  original array, and returning a local array is never safe. */

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" |- %p: %d\n", (void *)&arr[1], arr[1]);
    printf(" |- %p: %d\n", (void *)&arr[2], arr[2]);
    printf(" +- %p: %d\n", (void *)&arr[3], arr[3]);

    return 0;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("x (%p): %p\n", (void *)&x, (void *)x);
    printf("y (%p): %p\n", (void *)&y, (void *)y);
}

void reverse(int arr[], int len) {
    /* When an array is passed to a function, it decays into a pointer; "arr"
     *  is secretly a pointer, but the pointer and array syntax is largely
     *  interchangeable. */
    int i;

    for (i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);
    }
}
