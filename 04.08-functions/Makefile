# To compile both "main.o" and "add.o" into a single executable "add":
add: main.o add.o
	gcc -o add main.o add.o

# To compile just "add.c" into a the object file "add.o", which will contain
#  machine instructions that do not yet form a complete program:
add.o: add.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c add.c

# Note that "main.c" copy-pastes "add.h", so "add.h" ought to be a dependency
#  of "main.o", but it doesn't need to be specified in the compiler command:
main.o: main.c add.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c main.c
