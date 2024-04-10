#include <stdio.h>

void swap(int, int);

int main(void) {
    int z = 1, w = 2;

    swap(z, w);

    printf("z: %d\n", z);
    printf("w: %d\n", w);

    return 0;
}

void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}
