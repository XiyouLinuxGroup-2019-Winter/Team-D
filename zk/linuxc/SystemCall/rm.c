#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("./app <filename>");
        exit(0);
    }
    int i = 0;
    while (--argc > 0) {
        int ret = unlink(argv[++i]);
        if (ret < 0) {
            perror("unlink");
            exit(1);
        }
    }
    return 0;
}