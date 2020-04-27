#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        int i;
        printf("the child pid is %d\n", getpid());
        for (i = 3; i > 0; --i) {
            printf("This is the child\n");
            sleep(1);
        }
        exit(3);
    } else {
        printf("I am parent, my child pid = %d\n", pid);
        int stat_val;
        waitpid(pid, &stat_val, 0);
        if (WIFEXITED(stat_val)) {
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        } else if (WIFSIGNALED(stat_val)) {
            printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
        }
    }
    return 0;
}