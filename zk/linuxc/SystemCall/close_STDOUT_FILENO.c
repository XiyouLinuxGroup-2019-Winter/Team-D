#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    // 关闭标准输出
    close(STDOUT_FILENO);
    int fd;
    // 创建的文件的文件描述符是1
    fd = open("test.c", O_CREAT | O_RDWR | O_TRUNC, 0664);
    printf("fd = %d\n", fd);
    if (fd < 0) {
        perror("open test");
        exit(1);
    }
    // printf只知道向文件描述符是1的关联的文件里面写, 所以helloworld写到了test文件里 
    printf("helloworld");
    close(fd);

    return 0;
}

