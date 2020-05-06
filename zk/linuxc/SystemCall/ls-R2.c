#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_PATH 1024

void dirwalk(char *dir, void(*func)(char *)) {
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dirp;
    if((dirp = opendir(dir)) == NULL) {
        perror("opendir");
        return;
    }
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
            continue;
        } 
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
            fprintf(stderr, "dirwalk:name %s %s too long\n", dir, dp->d_name);
        } else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*func)(name);
        }
    }
    closedir(dirp);
}

void fsize(char *name) {
    struct stat stbuf;
    
    if (stat(name, &stbuf) == -1) {
        perror("stat");
        return;
    } else {
        if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
            dirwalk(name, fsize);
        }
        printf("%8ld %s\n", stbuf.st_size, name);
    }
}

int main(int argc, char *argv[])
{
    int i = 0;
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(argv[++i]);
        }
    }

    return 0;
}

