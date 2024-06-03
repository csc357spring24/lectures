#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    uint32_t ipaddr;

    /* This program, the client, will actively attempt to connect to the
     *  existing, already running server. In order to establish a connection,
     *  we must first know the server's address. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* For simplicity, we assume the first address, per the hostname and port
     *  given as command line arguments, will always work. */

    getaddrinfo(argv[1], argv[2], &hints, &addr);
    ipaddr = ntohl(((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

    printf("%d.%d.%d.%d\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
