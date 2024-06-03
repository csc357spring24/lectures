#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;

    /* This program, the server, will passively wait for new clients to attempt
     *  to connect to it. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /* For simplicity, we assume the first of our own addresses, populated by
     *  the sockets library, will alwyas work. */

    getaddrinfo(NULL, argv[1], &hints, &addr);

    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
