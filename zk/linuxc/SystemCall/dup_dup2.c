#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd, save_fd;
    char msg[] = "This is a test\n";

    fd = open("a.c", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    // fd = 3 -> a.c
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    save_fd = dup(STDOUT_FILENO);
    // save_fd = 4 ->STDOUT_FILENO
    dup2(fd, STDOUT_FILENO);
    // 1 -> fd -> a.c
    close(fd);
    write(STDOUT_FILENO, msg, strlen(msg));
    // msg写到了a.c文件中
    // printf("Hello World"); 打印到了a.c中
    // 完成了输出重定向
    dup2(save_fd, STDOUT_FILENO);
    write(STDOUT_FILENO, msg, strlen(msg));
    // 写到了屏幕上
    close(save_fd);
    return 0;
}
