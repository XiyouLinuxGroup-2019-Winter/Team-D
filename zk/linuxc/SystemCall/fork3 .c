#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    switch(pid) {
    case 0:
        printf("Child process is running, Child Process Return is %d, ParentPid is %d\n", pid, getppid());
        break;
    case -1:
        perror("Process creation failed\n");
        break;
    default:
        printf("Parent Process is running, Child Pid is %d, Parent Pid is %d\n", pid, getpid());
        break;
    }
    return 0;
}

