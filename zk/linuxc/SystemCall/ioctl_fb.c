#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <linux/fb.h> // screeninfo头文件
#include <sys/ioctl.h> // ioctl函数头文件

int main()
{
    int fd;
    struct fb_var_screeninfo fb_info;
    fd = open("/dev/fb0", O_RDONLY);
    if (fd < 0) {
        perror("open /dev/fb0");
        exit(1);
    }
    ioctl(fd, FBIOGET_VSCREENINFO, &fb_info);
    printf("row = %d\nCol = %d\n", fb_info.xres, fb_info.yres);

    close(fd);
    return 0;
}

