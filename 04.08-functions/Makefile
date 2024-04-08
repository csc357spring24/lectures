# To combine both "main.o" and "add.o" into a single executable "add":
add: main.o add.o
	gcc -o add main.o add.o

# Note that "main.c" copy-pastes "add.h", so "add.h" ought to be a dependency
#  of "main.o", but it doesn't need to be specified in the compiler command:
main.o: main.c add.h
	gcc -Wall -Wextra -Werror -ansi -pedantic -c main.c

# To compile just "add.c" into the object file "add.o", which will contain the
#  compiled machine instructions, but is not yet a complete program:
add.o: add.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c add.c
