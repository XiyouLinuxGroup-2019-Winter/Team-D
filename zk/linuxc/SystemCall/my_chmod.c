#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    char *path;
    int mode, mode_u, mode_g, mode_o;

    if (argc < 3) {
        printf("error\n");
        exit(0);
    }

    mode = atoi(argv[1]);
    mode_u = mode / 100;
    mode_g = (mode - mode_u * 100) / 10;
    mode_o = mode - mode_u * 100 - mode_g * 10;
    mode = mode_u * 8 * 8 + mode_g * 8 + mode_o;
    path = argv[2];

    if (chmod(path, mode) == -1) {
        perror("chmod error\n");
        exit(1);
    }

    return 0;
}

