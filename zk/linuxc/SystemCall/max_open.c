#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// unistd == unix standard unix 标准头文件
// fcntl == file control

int main(int argc, char *argv[])
{
    int fd;
    char name[2000];
    int i = 0;
    while (1) {
        sprintf(name, "file%d", ++i);
        fd = open(name, O_CREAT, 0777);
        if (fd == -1) {
            exit(1);
        }
        printf("%d\n", i);
    }

    return 0;
}

