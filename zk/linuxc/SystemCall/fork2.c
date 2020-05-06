#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    int cnt = 0;
    switch(pid) {
    case 0:
        while (cnt != 3) {
            printf("A background process, PID:%d\n, ParentID:%d\n", getpid(), getppid());
            sleep(3);
            cnt++;
        }
    case -1:
        perror("Process creation failed\n");
        exit(1);
    default:
        printf("I am Parent process, my pid is %d\n", getpid());
        exit(0);
    }
    exit(0);
    return 0;
}

