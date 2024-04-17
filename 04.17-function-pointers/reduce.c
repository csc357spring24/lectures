#include <stdio.h>

int reduce(int[], int);

int main(void) {
    int arr[] = {1, 2, 3, 4};

    printf("reduce(arr, 4, add): %d\n", reduce(arr, 4));

    return 0;
}

int reduce(int arr[], int n) {
    int val = arr[0], i;

    for (i = 1; i < n; i++) {
        val += arr[i];
    }

    return val;
}
