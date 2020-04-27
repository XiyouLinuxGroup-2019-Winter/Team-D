#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = 0;
    int n = 3;
    while (n--) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) {
        printf("I am child %d\n", getpid());
        sleep(3);
    } else if (pid > 0) {
        pid_t pid_c;
        while (1) {
            // pid_c = wait(NULL);
            sleep(1);
            printf("I am parent\n");
            pid_c = waitpid(0, NULL, WNOHANG);
            if (pid_c == -1) {
                printf("没有子进程可以回收\n");
                continue;
            } else {
                printf("wait for child %d\n", pid_c);
            }
            if (pid_c > 0) {
                n++;
                if (n == 2) {
                    break;
                }
            }
        }
    }
    return 0;
}