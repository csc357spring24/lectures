#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    uint32_t ipaddr;
    int fd, client, n;
    char buf[4];

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
    bind(fd, addr->ai_addr, addr->ai_addrlen);
    listen(fd, 1);

    struct sockaddr_storage tmp;
    socklen_t len = sizeof(struct sockaddr_storage);
    client = accept(fd, (struct sockaddr *)&tmp, &len);
    ipaddr = ntohl(((struct sockaddr_in *)&tmp)->sin_addr.s_addr);
    printf("Accepted from %d.%d.%d.%d\n",
     (ipaddr & 0xFF000000) >> 24,
     (ipaddr & 0x00FF0000) >> 16,
     (ipaddr & 0x0000FF00) >> 8,
     (ipaddr & 0x000000FF) >> 0);

    /* Instead of repurposing the existing socket, which is already bound and
     *  listening for future connections, accepting a connection creates a new
     *  socket dedicated to communications with that client. */

    while ((n = read(client, buf, 4)) > 0) {
        fwrite(buf, sizeof(char), n, stdout);
    }

    close(client);
    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
