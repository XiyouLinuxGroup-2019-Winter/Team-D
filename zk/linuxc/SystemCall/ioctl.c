#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
    struct winsize size;
    if (isatty(STDOUT_FILENO) == 0) {
        exit(1);
    }
    // 获得终端窗口大小
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0) {
        perror("ioctl TINCGWINSZ error");
        exit(1);
    }
    printf("row = %d\n, columns = %d\n", size.ws_row, size.ws_row);

    return 0;
}

