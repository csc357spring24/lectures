#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int main(int argc, char *argv[]) {
    struct addrinfo hints = {0}, *addr;
    int fd, n;
    struct pollfd clients[17];

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
    listen(fd, 16);

    /* To support up to 16 clients, we need to poll up to 17 sockets: the 16
     *  sockets connected to our clients, and the original socket created to
     *  listen for new connections. */

    clients[0].fd = fd;
    clients[0].events = POLLIN;
    n = 1;

    while (poll(clients, n, n > 1 ? -1 : 10000) > 0) {

        /* Since "poll" does not know if one file descriptor is more
         *  important than any other, it only tells us how many were ready
         *  for I/O; we have to search through the descriptors. */
        int i;

        for (i = 0; i < n; i++) {
            if (clients[i].revents & POLLIN) {
                if (clients[i].fd == fd) {
                    struct sockaddr_storage tmp;
                    socklen_t len = sizeof(struct sockaddr_storage);
                    uint32_t ipaddr;

                    /* By making sockets connected to clients non-blocking,
                     *  if there is no data available to be read, the read will
                     *  fail with -1 instead of waiting for more data. */

                    clients[n].fd = accept(fd, (struct sockaddr *)&tmp, &len);
                    fcntl(clients[n].fd, F_SETFL, O_NONBLOCK);
                    clients[n].events = POLLIN;
                    n++;

                    ipaddr = ntohl(((struct sockaddr_in *)&tmp)->sin_addr.s_addr);
                    printf("Accepted from %d.%d.%d.%d\n",
                     (ipaddr & 0xFF000000) >> 24,
                     (ipaddr & 0x00FF0000) >> 16,
                     (ipaddr & 0x0000FF00) >> 8,
                     (ipaddr & 0x000000FF) >> 0);
                }
                else {
                    char buf[4];
                    int m;

                    /* Ordinarily, "read" is a blocking call -- if the client
                     *  has not sent any data but also has not closed its
                     *  socket, then this will wait indefinitely. */

                    while ((m = read(clients[i].fd, buf, 4)) > 0) {
                        write(STDOUT_FILENO, buf, sizeof(char) * m);
                    }

                    /* Only if the client has closed its socket or if something
                     *  went wrong will we close our socket. Otherwise, there
                     *  is could be more data in the future. */

                    if (m == 0 || errno != EAGAIN) {
                        close(clients[i].fd);
                        clients[i] = clients[n - 1];
                        n--;
                    }
                }
            }
        }
    }

    close(fd);
    freeaddrinfo(addr);

    return EXIT_SUCCESS;
}
