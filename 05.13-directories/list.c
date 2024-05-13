#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    if (stat(argv[1], &buf) < 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("\"%s\" -> %ld (%ld bytes in %ld blocks)\n",
     argv[1], (long)(buf.st_ino), (long)(buf.st_size), (long)(buf.st_blocks));

    return EXIT_SUCCESS;
}
