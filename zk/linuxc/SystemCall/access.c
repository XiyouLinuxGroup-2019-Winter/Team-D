#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    if (access("abc", F_OK) < 0) {
        perror("abc");
        exit(1);
    }
    printf("abc is ok\n");

    return 0;
}

