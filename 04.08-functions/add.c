#include <stdio.h>

int main(void) {
    printf("add(1, 2): %d\n", add(1, 2));

    return 0;
}

int add(int x, int y) {
    int z = x + y;

    return z;
}
