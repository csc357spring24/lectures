#include <stdio.h>
#include "pair.h"

/* In C, everything is pass-by-value, and the value of a structure is the whole
 *  structure. If we want changes made inside a function to be communicated
 *  back to the caller, we need to return the whole structure: */
Pair foo(Pair pair) {
    pair.first = 5;

    return pair;
}

/* In C, if we wish to opt-in to pass-by-reference behavior, we can do so at
 *  any time simply by passing a pointer instead of an actual value -- note
 *  that the dot operator has precedence over the dereference: */
void bar(Pair *pair) {
    (*pair).first = 6;
    pair->second = 7;
}

int main(void) {
    /* To instantiate a variable of type "Pair": */
    Pair pair = {1, 2};

    /* Since we have defined a new type, the compiler has no way of knowing how
     *  to generally operate on values of that type. The only allowable
     *  operations are accessing members: */
    pair.first = 3;
    pair.second = 4;

    /* ...assigning one structure to another: */
    pair = foo(pair);

    /* ...and getting the address of a structure: */
    bar(&pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    return 0;
}
