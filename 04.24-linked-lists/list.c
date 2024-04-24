#include <stdlib.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate() {
    List *lst = (List *)malloc(sizeof(List));

    /* Memory dynamically allocated with malloc is not automatically zeroed
     *  out; if we want zeroes there, we should put zeroes there: */

    lst->head = NULL;
    lst->size = 0;

    return lst;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    Node *node = lst->head;

    while (node != NULL) {
        Node *next = node->next;
        free(node);
        node = next;
    }

    /* TODO: This only frees the List, not its Nodes... */

    free(lst);
}

/* lstget: Gets an element in a linked list. */
void *lstget(List *lst, int idx) {
    return NULL;
}

/* lstset: Sets an element in a linked list. */
int lstset(List *lst, int idx, void *val) {
    return 0;
}

/* lstadd: Adds an element to a linked list. */
int lstadd(List *lst, int idx, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    if (idx == 0) {
        node->next = lst->head;
        lst->head = node;
    }
    else {
        Node *prev = lst->head;
        int i;

        for (i = 0; i < idx - 1; i++) {
            prev = prev->next;
        }

        node->next = prev->next;
        prev->next = node;
    }

    lst->size++;

    /* If we cared to check for indexing out of bounds, we could do that and
     *  then potentially return a non-zero error code. */

    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
