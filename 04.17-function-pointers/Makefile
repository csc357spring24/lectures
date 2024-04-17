reduce: reduce.o add.o add.h max.o max.h
	gcc -o reduce reduce.o add.o max.o

reduce.o: reduce.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c reduce.c

add.o: add.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c add.c

max.o: max.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c max.c
