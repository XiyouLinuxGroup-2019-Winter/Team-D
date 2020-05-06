#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

void sys_err(char *str) {
    perror(str);
    exit(1);
}

int main() {
    int fd, len;
    int *p;
    fd = open("hello", O_RDWR);
    if (fd < 0) {
        sys_err("open");
    }
    len = lseek(fd, 0, SEEK_END);
    p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        sys_err("mmap");
    }
    p[0] = 0x30313233;
    munmap(p, len);
    close(fd);
    return 0;
}