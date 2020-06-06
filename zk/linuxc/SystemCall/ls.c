#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH 1024
#define MAX_FILE_NAME 255

void ls_display_current_dir(char *name) {
    struct dirent *dp;
    struct stat stbuf;
    DIR *dirp;
    if ((dirp = opendir(name)) == NULL) {
        perror("opendir");
        return; 
    }
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
            continue;
        }
        printf("%s\n", dp->d_name);
        }
    closedir(dirp);
}

void ls_l_display_current_dir(char *name) {
    struct dirent *dp;
    struct stat stbuf;
    DIR *dirp;
    if ((dirp = opendir(name)) == NULL) {
        perror("opendir");
        return;
    }
    while ((dp = readdir(dirp)) != NULL) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
            continue;
        }
        if (stat(dp->d_name, &stbuf) < 0) {
            perror("stat");
            return;
        } else {
            if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
                printf("d");
            } else if ((stbuf.st_mode & S_IFMT) == S_IFREG) {
                printf("-");
            } else if ((stbuf.st_mode & S_IFMT) == S_IFLNK) {
                printf("l");
            }
            if (stbuf.st_mode & S_IRUSR) {
                printf("r");
            } else {
                printf("-");
            } 
            if (stbuf.st_mode & S_IWUSR) {
                printf("w");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IXUSR) {
                printf("x");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IRGRP) {
                printf("r");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IWGRP) {
                printf("w");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IXGRP) {
                printf("x");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IROTH) {
                printf("r");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IWOTH) {
                printf("w");
            } else {
                printf("-");
            }
            if (stbuf.st_mode & S_IXOTH) {
                printf("x ");
            } else {
                printf("- ");
            }
            printf("%lu ", stbuf.st_nlink);
            // username groupname
            struct passwd *psd;
            struct group  *grp;
            psd = getpwuid(stbuf.st_uid);
            grp = getgrgid(stbuf.st_gid);
            printf("%s %s %ld  ", psd->pw_name, grp->gr_name, stbuf.st_size);
            // mtime
            char buf_time[32];
            strcpy(buf_time, ctime(&stbuf.st_mtime));
            buf_time[strlen(buf_time) - 1] = '\0';    //去掉换行符
            printf("%s ", buf_time);

            printf("%s\n", dp->d_name);





        }

    }
    closedir(dirp);
}

void ls_l_display_dir_or_file(char *name) {

}

int main(int argc, char *argv[])
{
    
    if (argc == 1) {
        int fd;
        ls_display_current_dir(".");
    } else if (argc == 2 && !strcmp(argv[1], "-l")) {
        ls_l_display_current_dir(".");
    } else if (argc == 3 && !strcmp(argv[1], "-l")) {
        ls_l_display_dir_or_file(argv[2]);
    }
    
    return 0;
}

