# Now that we know what we are doing, we can feel free to ignore any warnings
#  and switch to the latest version of the C standard with all of the extra
#  GNU extensions:
CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: copy fcopy

debug: CFLAGS += -g
debug: clean all

copy: copy.o
	gcc -o copy copy.o

fcopy: fcopy.o
	gcc -o fcopy fcopy.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
