/* To define a function that takes two ints and returns a third int: */
int add(int x, int y) {
    /* Functions create new local scopes, and the beginning of a funciton is
     *  thus a valid place to declare a new local variable: */
    int z = x + y;

    return z;
}
