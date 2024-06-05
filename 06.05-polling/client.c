#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    uint32_t ipaddr;
    int fd, n;
    char buf[4];

    /* This program, the client, will actively attempt to connect to the
     *  existing, already running server. In order to establish a connection,
     *  we must first know the server's address. */

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* For simplicity, we assume the first address, per the hostname and port
     *  given as command line arguments, will always work. */

    getaddrinfo(argv[1], argv[2], &hints, &addr);
    fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    connect(fd, addr->ai_addr, addr->ai_addrlen);

    ipaddr = ntohl(((struct sockaddr_in *)addr->ai_addr)->sin_addr.s_addr);
    printf("Connected to %d.%d.%d.%d\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    /* The client will simply take whatever the user types and send it out
     *  over the socket. */

    while ((n = read(STDIN_FILENO, buf, sizeof(char) * 4)) > 0) {
        int i = 0;

        while (i < n) {
            i += write(fd, buf + i, n - i);
        }
    }

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
