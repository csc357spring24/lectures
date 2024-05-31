#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addrs, *addr;

    /* This program, the client, will actively attempt to connect to the
     *  existing, already running server. In order to establish a connection,
     *  we must first know the server's address. */

    /* AF_INET requests a 32-bit IPv4 address; we could also use AF_INET6 for
     *  a 128-bit IPv6 address, or AF_UNSPEC if we didn't know or didn't care
     *  what type of address we got. */
    hints.ai_family = AF_INET;

    /* SOCK_STREAM requests a TCP connection, which is more reliable but
     *  slower; we could also use SOCK_DGRAM for UDP, which is faster but less
     *  reliable. */
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("unix1.csc.calpoly.edu", "22", &hints, &addrs);

    /* It is possible that a device has multiple addresses, in which case we
     *  need to iterate down a linked list of addresses to find one that
     *  works. */
    addr = addrs;

    while (addr != NULL) {
        uint32_t ipaddr = ntohl(((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);

        printf("%d.%d.%d.%d\n",
         (ipaddr & 0xFF000000) >> 24,
         (ipaddr & 0x00FF0000) >> 16,
         (ipaddr & 0x0000FF00) >> 8,
         (ipaddr & 0x000000FF) >> 0);

        addr = addr->ai_next;
    }

    freeaddrinfo(addrs);

    return EXIT_SUCCESS;
}
