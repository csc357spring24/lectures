#include <stdio.h>
#include "add.h"
#include "max.h"

int reduce(int[], int, int (*)(int, int));

int main(void) {
    int arr[] = {1, 2, 3, 4};
    char *str = "reduce(arr, 4, add): %d\n";

    /* "arr" is an ordinary array, stored on the runtime stack: */
    printf("arr: %p\n", (void *)arr);

    /* "str" is a pointer to an array in the read-only data segment: */
    printf("str: %p\n", (void *)str);

    /* "add" is the address of a machine instruction in the text segment: */
    printf("add: %p\n", (void *)add);
    printf("max: %p\n", (void *)max);

    printf(str, reduce(arr, 4, add));
    printf("reduce(arr, 4, max): %d\n", reduce(arr, 4, max));

    return 0;
}

/* Rather than defining two functions with the same loop but different loop
 *  bodies, we can instead define one function with that common loop, and have
 *  it take as argument a pointer to a function indicating what to do in the
 *  loop body: */
int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val = fn(val, arr[i]);
    }

    return val;
}
