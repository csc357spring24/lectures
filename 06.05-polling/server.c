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
    struct pollfd clients[17];
    int fd, n;

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
     *  sockets connected to our clients, and the 1 original socket created to
     *  listen for new connections. */

    clients[0].fd = fd;
    clients[0].events = POLLIN;
    n = 1;

    while (poll(clients, n, n > 1 ? -1 : 10000) > 0) {
        int i;

        /* Since "poll" does not know if one descriptor is more important than
         *  the rest, it just tells us how many are ready for I/O, and we can
         *  then search for which exactly those are. */

        for (i = 0; i < n; i++) {
            if (clients[i].revents & POLLIN) {
                if (clients[i].fd == fd) {
                    struct sockaddr_storage tmp;
                    socklen_t len = sizeof(struct sockaddr_storage);
                    uint32_t ip;

                    /* By making sockets connected to clients non-blocking,
                     *  if there is no data available to be read, the read will
                     *  fail with -1 instead of waiting for more data. */

                    clients[n].fd = accept(fd, (struct sockaddr *)&tmp, &len);
                    fcntl(clients[n].fd, F_SETFL, O_NONBLOCK);
                    clients[n].events = POLLIN;
                    n++;

                    ip = ntohl(((struct sockaddr_in *)&tmp)->sin_addr.s_addr);
                    printf("Accepted from %d.%d.%d.%d\n",
                     (ip & 0xFF000000) >> 24,
                     (ip & 0x00FF0000) >> 16,
                     (ip & 0x0000FF00) >> 8,
                     (ip & 0x000000FF) >> 0);
                }
                else {
                    char buf[4];
                    int m;

                    /* Ordinarily, "read" is a blocking call -- if the client
                     *  has not sent any data but also has not closed its
                     *  socket, the OS will pause execution indefinitely. */

                    while ((m = read(clients[i].fd, buf, 4)) > 0) {
                        write(STDOUT_FILENO, buf, sizeof(char) * m);
                    }

                    /* To break out of the loop, either the client has to close
                     *  the connection or something has to go wrong. If there
                     *  is simply no more data at the moment, we'll leave the
                     *  connection open. */

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
