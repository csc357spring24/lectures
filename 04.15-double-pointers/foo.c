#include <stdio.h>

/* Since an array of pointers is the address of the first element, which is
 *  itself a pointer, an array of pointers decays into a double pointer. Since
 *  array and pointer syntax is interchangeable, we can then index that
 *  double pointer twice, thereby offsetting and dereferencing it twice: */
void foo(int *mat[]) {
    mat[1][1] = 5;
}

/* Since indexing a true two-dimensional array requires knowing the length of
 *  each row, the parameter type must include that length: */
void bar(int mat[][2]) {
    mat[1][1] = 6;
}

/* Since indexing a true two-dimensional array requires knowing the length of
 *  each row, if that length is variable, we have to do the indexing math
 *  ourselves; the compiler doesn't know ahead of time: */
void bay(int *mat, int width) {
    *(mat + 1 * width + 1) = 7;
}

int main(void) {
    /* To declare an array of two pointers, which themselves are pointers to
     *  arrays of two integers each: */
    int r0[] = {1, 2}, r1[] = {3, 4};
    int *mat1[2];

    /* To declare an equivalent array of two arrays, which themselves are
     *  arrays of two integers each: */
    int mat2[][2] = {{1, 2}, {3, 4}};

    mat1[0] = r0;
    mat1[1] = r1;
    foo(mat1);

    printf("mat1: %p\n", (void *)mat1);
    printf(" |- %p: %p\n", (void *)&mat1[0], (void *)mat1[0]);
    printf(" |----- %p: %d\n", (void *)&mat1[0][0], mat1[0][0]);
    printf(" |----- %p: %d\n", (void *)&mat1[0][1], mat1[0][1]);
    printf(" |- %p: %p\n", (void *)&mat1[1], (void *)mat1[1]);
    printf(" |----- %p: %d\n", (void *)&mat1[1][0], mat1[1][0]);
    printf(" +----- %p: %d\n", (void *)&mat1[1][1], mat1[1][1]);

    bar(mat2);
    bay((int *)mat2, 2);

    printf("mat2: %p\n", (void *)mat2);
    printf(" |- %p: %p\n", (void *)&mat2[0], (void *)mat2[0]);
    printf(" |----- %p: %d\n", (void *)&mat2[0][0], mat2[0][0]);
    printf(" |----- %p: %d\n", (void *)&mat2[0][1], mat2[0][1]);
    printf(" |- %p: %p\n", (void *)&mat2[1], (void *)mat2[1]);
    printf(" |----- %p: %d\n", (void *)&mat2[1][0], mat2[1][0]);
    printf(" +----- %p: %d\n", (void *)&mat2[1][1], mat2[1][1]);

    return 0;
}
