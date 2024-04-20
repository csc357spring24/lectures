#include <stdlib.h>
#include <stdio.h>

int *pair(int, int);

int main(void) {
    int *arr;

    arr = pair(1, 2);

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    /* Since we the programmers uniquely know what our data represents, we the
     *  programmers uniquely know when we no longer need that data, and thus
     *  we are responsible for deallocating it: */
    free(arr);

    /* Freeing something that has already been freed is an error:
     * free(arr);
     * free(arr); */

    /* Freeing something that is in the middle of a block is an error:
     * free(arr + 1); */

    /* Freeing something that isn't on the heap is an error:
     * free(&arr); */

    return 0;
}

int *pair(int first, int second) {
    /* Returning a pointer to a local array is unsafe, since that array ceases
     *  to exist and its memory is repurposed after the function returns. If
     *  this array were global, then returning its pointer would be safe, but
     *  we would only ever be able to make one of them: */
    int *arr = (int *)malloc(sizeof(int) * 2);

    /* This is a pointer to a block of memory on the heap, not truly an array,
     *  but array and pointer syntax is interchangeable, and the compiler will
     *  let us pretend that it's actually an array: */
    arr[0] = first;
    arr[1] = second;

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return arr;
}
