reverse: reverse.o
	gcc -o reverse reverse.o

reverse.o: reverse.c
	gcc -Wall -Wextra -Werror -ansi -pedantic -c reverse.c

# By specifying as a target the name of a file that doesn't exist, we trick
#  Make into thinking that the command always has to be rerun. That command
#  includes the "-g" flag, which instructs the compiler to include the extra
#  information that is useful when debugging:
debug:
	gcc -Wall -Wextra -Werror -ansi -pedantic -g reverse.c
