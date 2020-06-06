#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd;

    if ((fd = open("test.c", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1) {
        perror("open");
        // printf("open:%s with errno:%d\n", strerror(errno), errno);
        // 从errno错误代码中获取错误信息strerror(errno)
        // 注意要包含头文件<errno.h>
        exit(1);
    } else {
        printf("Creat file success\n");
    }

    close(fd);
    return 0;
}

