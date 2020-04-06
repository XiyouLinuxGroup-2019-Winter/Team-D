#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MSG_TRY "trt again\n"
#define MSG_TIMEOUT "timeout\n"
#define SIZE 10

int main()
{
    char buf[SIZE];
    int fd, n, i;
    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open /dev/tty");
        exit(1);
    }
    for (i = 0; i < 5; i++) {
        n = read(fd, buf, sizeof(buf));
        if (n < 0) {
            if (errno == EAGAIN) {
                sleep(1);
                write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            } else {
                perror("read /dev/tty");
                exit(1);
            }
        } else {
            write(STDOUT_FILENO, buf, n);
            break;
        }
    }
    if (i == 5) {
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    }
    close(fd);

    return 0;
}

