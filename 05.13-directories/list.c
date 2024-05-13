#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat buf;

    /* Every process has a current working directory, relative to which all
     *  file system operations are performed. The current directory always has
     *  the special hidden filename ".": */

    chdir(argv[1]);
    dir = opendir(".");

    while ((entry = readdir(dir)) != NULL) {
        /* Each directory entry is only guaranteed to contain a filename and
         *  the number of the inode to which it is mapped. Any additional
         *  information must be gathered by calling stat: */
        if (stat(entry->d_name, &buf) < 0) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        printf("\"%s\" -> %ld (%ld bytes in %ld blocks)\n",
         entry->d_name, (long)(buf.st_ino), (long)(buf.st_size), (long)(buf.st_blocks));

        /* Note that a directory entry is only guaranteed to persist until the
         *  directory is closed or until readdir is called again. If we wish to
         *  save any of this information for later, we have to dynamically
         *  allocate our own copy. */
    }

    closedir(dir);

    return EXIT_SUCCESS;
}
