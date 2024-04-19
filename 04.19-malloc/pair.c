#include <stdlib.h>
#include <stdio.h>

int *pair(int, int);

int main(void) {
    int *arr;

    arr = pair(1, 2);

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    /* Since the entire purpose of the heap is allocate memory outside the
     *  constraints of the stack and the data segment, only we know when we
     *  are done with that memory, so only we know when it ought to be
     *  deallocated: */
    free(arr);

    /* Freeing something that has already been deallocated is an error:
     * free(arr);
     * free(arr); */

    /* Freeing something that is inside a block is an error:
     * free(arr + 1); */

    /* Freeing something that isn't even on the heap is an error:
     * free(&arr); */

    return 0;
}

int *pair(int first, int second) {
    /* Returning a pointer to a local array would be unsafe, because that local
     *  array would be deallocated on return. Returning a pointer to a global
     *  array would be incorrect, because we don't know how many globals we
     *  need at compile-time. */
    int *arr = (int *)malloc(sizeof(int) * 2);

    /* Since malloc doesn't know what type of data we plan to place in that
     *  memory, it returns a void pointer: a valid pointer, but one that cannot
     *  be dereferenced. Once that pointer is cast to an integer pointer, we
     *  can treat it as though it were an integer array: */
    arr[0] = first;
    arr[1] = second;

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return arr;
}
