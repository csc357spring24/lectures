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
    /* Freeing the List only frees the List; it does not free any of the Nodes
     *  contained within. Additionally, the Nodes have to be freed (or we have
     *  to save a pointer to the head) before we free the List otherwise we'll
     *  lose the pointer that enables us to access them. */

    Node *node = lst->head;

    while (node != NULL) {
        Node *next = node->next;
        free(node);
        node = next;
    }

    /* There is no need to set any of the head or next pointers back to NULL;
     *  the list is being deallocated, so we shouldn't need to care what its
     *  memory contains. */

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

    /* If we wanted to check for, for example, out-of-bounds indices, we could
     *  then return something other than 0 to indicate an error. */

    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
