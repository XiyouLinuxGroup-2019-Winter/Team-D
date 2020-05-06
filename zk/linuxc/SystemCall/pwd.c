#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 4096

int main()
{
    char buf[SIZE];

    chdir("/");
    printf("%s\n", getcwd(buf, sizeof(buf)));
     
    return 0;
}

