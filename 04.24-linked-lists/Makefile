list.o: list.c list.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c list.c

debug:
	gcc -Wall -Wextra -Werror -ansi -pedantic -g -c list.c

test: debug
	gcc -Wall -Wextra -Werror -ansi -pedantic -g listtests.c list.o
	valgrind --leak-check=full --show-leak-kinds=all ./a.out
