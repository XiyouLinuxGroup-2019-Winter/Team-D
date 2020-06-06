#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        while (1) {
            printf("I am child \n");
            printf("PID = %d\n", getpid());
            printf("parent PID = %d\n", getppid());
            sleep(1);
        }
    } else if (pid > 0) {
        sleep(3);
        printf("I am parent \n");
        printf("PID = %d\n", getpid());
        printf("parent PID = %d\n", getppid());
        exit(1);
    }
}