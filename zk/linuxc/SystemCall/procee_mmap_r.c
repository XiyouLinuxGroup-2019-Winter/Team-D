#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#define MAP_LEN 0x1000

struct Stu {
    int id;
    char name[20];
    char sex;
};

void sys_err(char *str, int exit_no) {
    perror(str);
    exit(exit_no);
}

int main(int argc, char *argv[]) {
    struct Stu *mm;
    int fd, i = 0;
    if (argc < 2) {
        printf("./a.out filename\n");
        exit(1);
    }
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        sys_err("open", 1);
    }
    mm = mmap(NULL, MAP_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED) {
        sys_err("mmap", 2);
    }
    close(fd);
    unlink(argv[1]);
    while (1) {
        printf("%d\n", mm->id);
        printf("%s\n", mm->name);
        printf("%c\n", mm->sex);
        sleep(1);
    }
    munmap(mm, MAP_LEN);
    return 0;
}