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
     *  constraints of the runtime stack and the data segment, only we the
     *  programmers know what its data represents, only we the programmers
     *  uniquely know when we no longer need that data, and thus we are
     *  responsible for deallocating it: */
    free(arr);

    /* Freeing something that has already been deallocated is an error:
     * free(arr);
     * free(arr); */

    /* Freeing something that is inside an allocated block is an error:
     * free(arr + 1); */

    /* Freeing something that isn't allocated on the heap is an error:
     * free(&arr); */

    return 0;
}

int *pair(int first, int second) {
    /* Returning a pointer to a local array is unsafe, since that array ceases
     *  to exist and its memory is repurposed after the function returns. If
     *  this array were global, then returning its pointer would be safe, but
     *  we would only ever be able to make one of them: */
    int *arr = (int *)malloc(sizeof(int) * 2);

    /* Since malloc doesn't know what type of data we plan to place in that
     *  memory, it returns a void pointer: a valid pointer, but one that cannot
     *  be dereferenced. Once that pointer is cast to an integer pointer, we
     *  can treat it as though it were an integer array: */
    arr[0] = first;
    arr[1] = second;

    return arr;
}
