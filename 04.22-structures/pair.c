#include <stdio.h>
#include "pair.h"

/* In C, everything is pass-by-value, and the value of a structure is the whole
 *  structure. If a function intends to modify a given structure, then it must
 *  return the resulting structure: */
Pair foo(Pair pair) {
    pair.first = 5;

    return pair;
}

/* If we want to opt-in to pass-by-reference behavior, we can always pass a
 *  pointer to a structure rather than the structure itself. Note that the dot
 *  operator has higher precedence than the dereference: */
void bar(Pair *pair) {
    (*pair).first = 6;
    pair->second = 7;
}

int main(void) {
    /* To instantiate a variable of type "struct Pair": */
    Pair pair = {1, 2};

    /* A structure definition introduces a new type. The compiler has no idea
     *  what this type represents, and so the only allowable operations are
     *  using the dot operator to access a member: */
    pair.first = 3;
    pair.second = 4;

    /* ...using the single equals operator to assign a structure: */
    pair = foo(pair);

    /* ...and using the single unary ampersand operator to get its address: */
    bar(&pair);

    printf("pair (%p):\n", (void *)&pair);
    printf(" |- first  (%p): %d\n", (void *)&pair.first, pair.first);
    printf(" +- second (%p): %d\n", (void *)&pair.second, pair.second);

    return 0;
}
