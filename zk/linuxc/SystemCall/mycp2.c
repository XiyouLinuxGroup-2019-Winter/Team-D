#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define SIZE 1000

int main(int argc, char *argv[])
{
    char buf[SIZE];
    if (argc < 3) {
        printf("./mycp src dest\n");
        exit(1);
    }
    int fd_src, fd_dest, len;
    fd_src = open(argv[1], O_RDONLY | O_EXCL);
    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_src < 0) {
        perror("open");
        exit(1);
    }
    if (fd_dest < 0) {
        perror("open");
        exit(1);
    }
    len = read(fd_src, buf, SIZE);
    if (len < 0) {
        perror("read");
        exit(1);
    }
    int n;
    n = write(fd_dest, buf, len);
    if (n < 0) {
        perror("write");
        exit(1);
    }
    close(fd_src);
    close(fd_dest);

    return 0;
}

