#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    int fd;
    char buf[] = "helloWrold\n";

    if (argc < 2) {
        printf("./app filename\n");
        exit(1);
    }

    umask(0);
    fd = open(argv[1], O_CREAT | O_RDWR | O_EXCL, 0777);
    if (fd == -1) {
        printf("file already exist\n");
        exit(1);
    }
    write(fd, buf, strlen(buf));
    close(fd);
    
    return 0;
}

