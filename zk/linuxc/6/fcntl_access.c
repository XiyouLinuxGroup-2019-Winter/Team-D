#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void my_err(const char *err_string, int line) {
    fprintf(stderr, "line:%d", line);
    perror(err_string);
    exit(1);
}

int main()
{
    int ret, access_mode, fd;

    if ((fd = open("test.c", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1) {
        my_err("open", __LINE__);
    }

    // 设置文件打开方式
    if ((ret = fcntl(fd, F_SETFL, O_APPEND)) < 0) {
        my_err("fcntl", __LINE__);
    }

    // 获取文件打开方式
    if ((ret = fcntl(fd, F_GETFL, 0)) < 0) {
        my_err("fcntl", __LINE__);
    }
    // O_ACCMOND是取得文件打开方式的掩码
    access_mode = ret & O_ACCMODE;
    if (access_mode == O_RDONLY) {
        printf("test.c access mode is read only");
    } else if (access_mode == O_WRONLY) {
        printf("test.c access mode is write only");
    } else if (access_mode == O_RDWR) {
        printf("test.c access mode is read and write");
    }

    if (ret & O_APPEND) {
        printf(", append");
    }
    if (ret & O_NONBLOCK) {
        printf(", nonblock");
    }
    if (ret & O_SYNC) {
        printf(", sync");
    }
    printf("\n");

    return 0;
}

