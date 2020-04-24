#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

void dirwalk(char *dir, void (*func)(char *)) {
    struct dirent *dp;
    DIR *dirp;
    char name[1024];

    if ((dirp = opendir(dir)) == NULL) {
        perror("opendir");
        exit(1);
    }
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
            continue;
        }
        sprintf(name, "%s/%s", dir, dp->d_name);
        (*func)(name);
    }
    closedir(dirp);
    rmdir(dir);
}


void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) < 0) {
        perror("stat");
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    } else {
        unlink(name);
    }
}

int main(int argc, char *argv[]) {
    // rmdir() 删除空目录前把所有目录的文件unlink掉
    if (argc < 3) {
        printf("./app -rf <filename>");
        exit(1);
    }
    int i = 1;
    while (--argc > 1) {
        fsize(argv[++i]);
    }
    return 0;
}