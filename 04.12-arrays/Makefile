reverse: reverse.o
	gcc -o reverse reverse.o

reverse.o: reverse.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c reverse.c

# By giving the target the name of a file that doesn't exist, we trick Make
#  into thinking that it always needs to run this command upon "make debug".
#  That command includes the "-g" flag, which instructs the compiler to put
#  any debug information into the executable.
debug:
	gcc -Wall -Wextra -Werror -ansi -pedantic -g reverse.c
