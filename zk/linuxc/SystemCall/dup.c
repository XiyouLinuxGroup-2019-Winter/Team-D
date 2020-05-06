#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    // fd = 3 -> test
    fd = open("test", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    int fd2 = open("test2", O_RDWR | O_CREAT, 0644);
    dup2(fd, STDIN_FILENO);
    dup2(fd2, STDOUT_FILENO);
    int num[6];
    for (int i = 0; i < 6; i++) {
        scanf("%d", &num[i]);
    }
    for (int i = 0; i < 6; i++) {
        printf("%d", num[i]);
    }
    return 0;
}