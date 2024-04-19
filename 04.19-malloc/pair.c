#include <stdio.h>

int *pair(int, int);

int main(void) {
    int *arr;

    arr = pair(1, 2);

    printf("arr: %p\n", (void *)arr);
    printf(" |- %p: %d\n", (void *)&arr[0], arr[0]);
    printf(" +- %p: %d\n", (void *)&arr[1], arr[1]);

    return 0;
}

int *pair(int first, int second) {
    int arr[2];

    arr[0] = first;
    arr[1] = second;

    return arr;
}
