#include <stdio.h>
#include "add.h"
#include "max.h"

int reduce(int[], int, int (*)(int, int));

int main(void) {
    int arr[] = {1, 2, 3, 4};
    char *str = "reduce(arr, 4, add): %d\n";

    printf("arr: %p\n", (void *)arr);
    printf("str: %p\n", (void *)str);
    printf("add: %p\n", (void *)add);
    printf("max: %p\n", (void *)max);

    printf(str, reduce(arr, 4, add));
    printf("reduce(arr, 4, max): %d\n", reduce(arr, 4, max));

    return 0;
}

/* Rather than defining two functions with the same loop, but different loop
 *  bodies, we could define one function with that one loop, and pass it a
 *  function pointer indicating what to do inside the loop body: */
int reduce(int arr[], int n, int (*fn)(int, int)) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val = fn(val, arr[i]);
    }

    return val;
}
