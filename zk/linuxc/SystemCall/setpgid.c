#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        printf("child process PID is %d\n", getpid());
        printf("Group ID of child is %d\n", getpgid(0));
        sleep(5);
        printf("Group ID of child is changed to %d\n", getpgid(0));
        exit(0);
    }

    sleep(1);
    setpgid(pid, pid);
    return 0;
}