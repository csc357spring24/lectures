CFLAGS = -Wall -Wextra -ansi -pedantic

# Arguably, warnings are fine as long as we're still testing and incrementally
#  developing; it's only once we build the final version of our code that we
#  don't want to see any warnings.

list.o: list.c list.h
	gcc $(CFLAGS) -Werror -c list.c

debug:
	gcc $(CFLAGS) -g -c list.c

test: debug
	gcc $(CFLAGS) -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
