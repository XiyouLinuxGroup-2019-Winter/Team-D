#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define MSG_TRY "try again\n"

int main()
{
    char buf[10];
    int n;
    int flags;
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(1);
    }
    while (1) {
        n = read(STDIN_FILENO, buf, 10);
        if (n < 0) {
            if (errno == EAGAIN) {
                sleep(1);
                write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            } else {
                perror("read");
                exit(1);
            }
        } else {
            write(STDOUT_FILENO, buf, n);
            break;
        }
    }
    return 0;
}

