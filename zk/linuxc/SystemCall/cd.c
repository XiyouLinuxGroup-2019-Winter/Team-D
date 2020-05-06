#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("./app <dirname>\n");
        exit(1);
    }
    if (argv[1] == NULL || strcmp(argv[1], "~") == 0) {
        char *home_path = getenv("HOME");
        if ((chdir(home_path) < 0)) {
            perror("chdir");
        }
    } else if (argv[1][0] == '~') {
        char *home_path = getenv("HOME");
        char *path = (char *) malloc(sizeof(char) * PATH_MAX);
        strcpy(path, home_path);
        strcat(path, argv[1] + 1);
        if ((chdir(path) < 0)) {
            perror("chdir");
        }
    } else {
        if ((chdir(argv[1]) < 0)) {
            perror("chdir");
        }
    }
    return 0;
}