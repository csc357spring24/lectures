/* To define a structure containing two ints. :*/
struct Pair {
    int first;
    int second;
};

/* To define "Pair" as a synonym for "struct Pair": */
typedef struct Pair Pair;

/* Structures may contain other structures of other types, but they may not
 *  contain structures of the same type -- we never actually want a truly
 *  "recursive" structure; we want "self-referential" structures... */
typedef struct Trip {
    Pair pair;
    int third;
} Trip;
