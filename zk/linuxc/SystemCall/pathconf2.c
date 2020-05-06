#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    printf("pipe buf size = %ld\n", fpathconf(fd[0], _PC_PIPE_BUF));
    return 0;
}
