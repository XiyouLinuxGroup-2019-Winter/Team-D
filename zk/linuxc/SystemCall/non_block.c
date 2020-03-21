#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MSG_TRY "try again\n"
#define SIZE 10

int main()
{
    char buf[SIZE];
    int fd, len;
    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open /dev/tty");
        exit(1);
    }
    // 文件以非阻塞方式打开
    // 如果没有数据, read函数就出错返回
    while (1) {
        len = read(fd, buf, sizeof(buf));
        if (len < 0) {
            if (errno == EAGAIN) {
                sleep(1);
                write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            } else {
                perror("read /dev/tty");
                exit(1);
            }
        } else {
            break;
        }
    }
    write(STDOUT_FILENO, buf, len);
    close(fd);
    return 0;
}

