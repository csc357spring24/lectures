#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, client, n;
    char buf[5];

    /* This program, the server, will passively wait for new clients to attempt
     *  to connect to it. In order to listen for new connections, we need to
     *  know our own address. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /* For simplicity, we assume the first of our own addresses, populated by
     *  the sockets library, will alwyas work. */

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    /* Unlike the client, the server plans to listen for new connections on a
     *  specific port, so the socket must be "bound" to that port. */

    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* The existing socket is already bound and listening for new connections;
     *  accept creates a new socket for use with the newly connected client,
     *  rather than repurposing the existing connection, in case we want to
     *  accept additional clients later. */

    client = accept(fd, NULL, NULL);

    while ((n = read(client, buf, 4)) > 0) {
        buf[n] = '\0';
        printf("Client sent \"%s\".\n", buf);
    }

    close(client);
    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
