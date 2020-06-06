#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>

#define FILE_CHANGED 0
#define FILE_CREATE  -1
#define FILE_DELETE  -2

void daemonize() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) {
        exit(0);
    }

    setsid();
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }
    umask(0);
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

typedef struct Node {
    char filename[NAME_MAX];
    long time;
    struct Node *next;
}Node;

typedef Node* LinkedList;

LinkedList p;

void initLinkedList() {
    p = (LinkedList)malloc(sizeof(Node));
    p->next = NULL;
}

int addTailLinkedList(char *name, long t) {
    LinkedList  newNode = (LinkedList)malloc(sizeof(Node));
    LinkedList cur = p;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    strcpy(newNode->filename, name);
    newNode->time = t;
    cur->next = newNode;
    newNode->next = NULL;
    return 1;
}

int displayLinkedList() {
    LinkedList cur = p;
    char *home_path = getenv("HOME");
    DIR *dirp = opendir(home_path);
    struct dirent *dp;
    struct stat statbuf;
    int flag = 0;
    while ((dp = readdir(dirp)) != NULL) {
        stat(dp->d_name, &statbuf);
        long t = statbuf.st_mtime;
        while (cur->next != NULL) {
            char *name = cur->next->filename;
            long time = cur->next->time;
            if (strcmp(dp->d_name, name) == 0) {
                if (time == t) {
                    return 1;
                } else {
                    return FILE_CHANGED;
                }
            }
            cur = cur->next;
        }
    }
}


int main() {
    daemonize();
    char *home_path = getenv("HOME");
    DIR *dirp = opendir(home_path);
    struct dirent *dp;
    struct stat statbuf;
    while ((dp = readdir(dirp)) != NULL) {
        stat(dp->d_name, &statbuf);
        addTailLinkedList(dp->d_name, statbuf.st_mtime);
    }
    while (1) {
        int fd;
        char buf[1024];
        if ((fd = open("/tmp/filechanged.log", O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0) {
            perror("open");
            exit(1);
        }
        int result = displayLinkedList();
        if (result == FILE_CHANGED) {
            sprintf(buf, "file was changed");
            write(fd, buf, strlen(buf));
        } else if (result == FILE_CREATE) {
            sprintf(buf, "file was create");
            write(fd, buf, strlen(buf));
        } else if (result == FILE_DELETE) {
            sprintf(buf, "file was delete");
            write(fd, buf, strlen(buf));
        }
        sleep(3);
    }
}