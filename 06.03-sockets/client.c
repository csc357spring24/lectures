#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    uint32_t ipaddr;
    int fd;

    /* This program, the client, will actively attempt to connect to the
     *  existing, already running server. In order to establish a connection,
     *  we must first know the server's address. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* For simplicity, we assume the first address, per the hostname and port
     *  given as command line arguments, will always work. */

    getaddrinfo(argv[1], argv[2], &hints, &addr);
    ipaddr = ntohl(((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

    /* All I/O is file I/O, and sockets are no exception, just like the
     *  terminal, actual files, and pipes. */

    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    connect(fd, addr->ai_addr, addr->ai_addrlen);

    printf("Connected to %d.%d.%d.%d\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    /* It is possible that the entire message cannot be sent at once, in which
     *  case it is our responsibility to try sending the rest later. */

    char buf[] = "Hello, world!";
    int i = 0;

    while (i < 13) {
        i += write(fd, buf + i, 13 - i);
    }

    printf("Sent \"%s\".\n", buf);

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
