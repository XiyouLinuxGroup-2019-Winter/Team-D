#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// 创建守护进程
void daemonize() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) {
        exit(0);
    }

    setsid();
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }
    umask(0);
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

int main() {
    daemonize();
    while (1) {
        // 执行守护进程的任务, 每隔3秒往/tmp/daemon.log文件里写入当前时间
        int fd;
        if ((fd = open("/tmp/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0) {
            perror("open");
            exit(1);
        }
        time_t t;
        time(&t);
        char buf[1024];
        ctime_r(&t, buf);
        write(fd, buf, strlen(buf));
        sleep(3);
    }
}