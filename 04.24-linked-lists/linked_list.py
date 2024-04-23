# Implements a linked list.
# CSC 202, https://github.com/csc202summer22/lectures
# Given pseudocode, Summer '22


class List:
    """ An ordered collection of elements """

    def __init__(self):
        # The head of the backing linked list:
        self.head = None
        # The number of elements in this list:
        self.size = 0


class Node:
    """ A single node in a linked list """

    def __init__(self, value, next):
        # The value contained in this node:
        self.value = value
        # The next node in the linked list:
        self.next = next


def get(lst, idx):
    # Start with the current node being the head.
    # For i from 0 to idx, do:
    #     Set the current node to the current node's next.
    # Return the current node's value.
    pass


def set(lst, idx, value):
    # Start with the current node being the head.
    # For i from 0 to idx, do:
    #     Set the current node to the current node's next.
    # Set the current node's value to the given value.
    pass


def add(lst, idx, value):
    # Create a new node containing the given value.
    # If adding to the beginning of the list, then:
    #     Set the new node's next to the head.
    #     Set the head to the new node.
    # Else, do:
    #     Start with the previous node being the head.
    #     For i from 0 to idx - 1, do:
    #         Set the previous node to the previous node's next.
    #     Set the new node's next to the previous node's next.
    #     Set the previous node's next to the new node.
    # Increment the size.
    pass


def remove(lst, idx, value):
    # If removing from the beginning of the list, then:
    #     Set the head to the head's next.
    # Else, do:
    #     Start with the previous node being the head.
    #     For i from 0 to idx - 1, do:
    #         Set the previous node to the previous node's next.
    #     Set the previous node's next to the previous node's next's next.
    # Decrement the size.
    # Return the "unlinked" node's value.
    pass
