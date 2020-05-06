#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define SIZE 8192

int main(int argc, char *argv[]) {
    char buf[SIZE];
    int fd_src, fd_dest, len;
    if (argc < 3) {
        printf("./a.out src dest\n");
        exit(1);
    }
    fd_src = open(argv[1], O_RDONLY);
    fd_dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);

    while ((len = read(fd_src, buf, sizeof(buf))) > 0) {
        write(fd_dest, buf, len);
    }

    close(fd_dest);
    close(fd_src);
    return 0;
}