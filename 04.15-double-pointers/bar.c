#include <stdio.h>

/* Since the value of an array is the address of its first element, the value
 *  of an array of pointers is the address of its first pointer, which decays
 *  into a double pointer. Pointer and array syntax is interchangeable, so
 *  even though this is actually a double pointer, we can index it twice: */
void foo(int *mat[]) {
    mat[1][1] = 5;
}

/* Since the value of an array is the address of its first element, the value
 *  of a two-dimensional array is the address of the first element in the first
 *  "inner" array. The compiler must know how long each "inner" array is in
 *  order to make the indexing math work out: */
void bar(int mat[][2]) {
    mat[1][1] = 6;
}

/* Since the compiler must know how long each "inner" array is, the above
 *  can only take n x 2 arrays, not arbitrary n x m arrays. The compiler, in
 *  this case, doesn't know how to make the indexing math work out, but if we
 *  take that length as an argument, we can do the math for the compiler: */
void bay(int *mat, int width) {
    *(mat + 1 * width + 1) = 7;
}

int main(void) {
    /* To declare an array of two pointers, which happen to be pointers to
     *  arrays of two integers each: */
    int r0[] = {1, 2}, r1[] = {3, 4};
    int *mat1[2];

    /* To declare a true two-dimensional array of two arrays, which contain
     *  two integers each: */
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
