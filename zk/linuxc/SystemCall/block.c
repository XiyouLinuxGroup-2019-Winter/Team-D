#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    char buf[100];
    int len;

    len = read(STDIN_FILENO, buf, sizeof(buf));
    if (len < 0) {
        perror("read");
        exit(1);
    }
    write(STDOUT_FILENO, buf, len);

    return 0;
}

