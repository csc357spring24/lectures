CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: sporkbomb

debug: CFLAGS += -g
debug: clean all

sporkbomb: spork.o spork.h sporkbomb.o
	gcc -o sporkbomb sporkbomb.o spork.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
