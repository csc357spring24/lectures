CFLAGS = -Wall -Wextra -ansi -pedantic

list.o: list.c list.h
	gcc $(CFLAGS) -Werror -c list.c

# Arguably, warnings are okay while we're still incrementally testing and
#  debugging; it's only once we build the final version of our code that we
#  want to address all of the warnings.

debug:
	gcc $(CFLAGS) -g -c list.c

test: debug
	gcc $(CFLAGS) -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
