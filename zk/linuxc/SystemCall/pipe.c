#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pid_t pid;
    char str[] = "hello world";
    char buf[1024];

    // fd[0] 读端
    // fd[1] 写端
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    // 父写子读
    if (pid > 0) {
        // 父进程里, 关闭父读
        close(fd[0]);
        sleep(5);
        write(fd[1], str, strlen(str));
        close(fd[1]);
        wait(NULL);
    } else if (pid == 0) {
        // 子进程里, 关闭子写
        int len, flags;
        close(fd[1]);
        flags = fcntl(fd[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(fd[0], F_SETFL, flags);
    tryagain:
        len = read(fd[0], buf, sizeof(buf));
        if (len == -1) {
            if (errno == EAGAIN) {
                write(STDOUT_FILENO, "try again\n", 10);
                sleep(1);
                goto tryagain;
            } else {
                perror("read");
                exit(1);
            }
        }
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}