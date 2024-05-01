CFLAGS = -Wall -Wextra -std=gnu11 -pedantic

all: pack

debug: CFLAGS += -g
debug: clean all

pack: pack.o
	gcc -o pack pack.o

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f *.o
