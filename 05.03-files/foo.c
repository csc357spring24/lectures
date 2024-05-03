#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct stat buf;

    if (stat(argv[1], &buf) < 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    /* Note that of all the information that can be gleaned by stat'ing a file,
     *  the filename is not one of them. Files do not have names; files have
     *  numbers, and their names are mapped to their numbers by their parent
     *  directories. */

    printf("device: %ld\n", (long)(buf.st_dev));
    printf("inode:  %ld\n", (long)(buf.st_ino));
    printf("size:   %ld\n", (long)(buf.st_size));
    printf("blocks: %ld\n", (long)(buf.st_blocks));

    return EXIT_SUCCESS;
}
