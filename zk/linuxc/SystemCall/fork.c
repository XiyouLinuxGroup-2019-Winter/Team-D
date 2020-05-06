#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid > 0) {
        while (1) {
            printf("I am parent process\n");
            printf("my pid = %d\n", getpid());
            printf("my parent pid = %d\n", getppid());
            sleep(5);
        }
    } else if (pid == 0) {
        while (1) {
            printf("I am child process\n");
            printf("my pid = %d\n", getpid());
            printf("my parent pid = %d\n", getppid());
            sleep(10);
        }
    } else {
        perror("fork");
        exit(1);
    }
    return 0;
}