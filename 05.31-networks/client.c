#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addrs, *addr;

    /* This program, the client, will actively attempt to connect to an
     *  existing, already-running server. */

    /* AF_INET requests a 32-bit IPv4 address; if we wanted a 128-bit IPv6
     *  address, we would use AF_INET6; if we didn't know or didn't care, we
     *  would use AF_UNSPEC. */
    hints.ai_family = AF_INET;

    /* SOCK_STREAM requests a TCP connection; if we wanted a UDP connection,
     *  we would use SOCK_DGRAM for a faster but less reliable connection. */
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("unix1.csc.calpoly.edu", "22", &hints, &addrs);

    /* It is possible that a connection could be established over multiple
     *  alternative addresses, so getaddrinfo produces a linked list of
     *  address structures. */
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

    /* None of this establishes a connection or even guarantees that a
     *  connection would be accepted. It simply provides the information
     *  necessary to attempt a connection. */

    freeaddrinfo(addrs);

    return EXIT_SUCCESS;
}
