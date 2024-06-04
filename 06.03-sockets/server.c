#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, client;

    /* This program, the server, will passively wait for new clients to attempt
     *  to connect to it. In order to listen for new connections, we need to
     *  know our own address. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /* For simplicity, we assume the first of our own addresses, populated by
     *  the sockets library, will always work. */

    getaddrinfo(NULL, argv[1], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

    /* If clients are to connect to us, they have to know what port we are
     *  using, so our socket has to be "bound" to a known port. */

    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    /* Instead of repurposing the existing socket, which is already bound and
     *  listening for future connections, this creates a new socket dedicated
     *  to communications with the client we just accepted. */

    client = accept(fd, NULL, NULL);
    char buf[5];
    int n;

    while ((n = read(client, buf, 4)) > 0) {
        buf[n] = '\0';
        printf("Client sent \"%s\".\n", buf);
    }

    close(client);
    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
