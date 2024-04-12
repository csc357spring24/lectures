#include <stdio.h>

void swap(int *, int *);
void reverse(int[], int);

int main(void) {
    int arr[4] = {1, 2, 3, 4};

    /* Arrays are just addresses of contiguous blocks of memory; they have no
     *  length attribute, and the length must be passed separately if needed: */
    reverse(arr, 4);

    /* Since the value of an array is a reference to its first element, any
     *  modifications to the array within a function will be reflected outside
     *  that function: */
    
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
    /* Here, "arr" is secretly a pointer, both pointers and arrays are just
     *  addresses, and the compiler will let us use pointer and array syntax
     *  interchangeably: */
    int i;

    for (i = 0; i < len / 2; i++) {
        swap(&arr[i], &arr[len - 1 - i]);
    }
}
