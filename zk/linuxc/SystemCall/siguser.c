#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int fd[2];

void do_sig_parent(int num) {
    static int n = 0;
    printf("I am parent\n");
    printf("Now is %d\n", n);
    n += 1;
}

void do_sig_child(int num) {
    static int n = 0;
    printf("I am child\n");
    printf("Now is %d\n", n);
    n += 1;
}

int main() {
    pid_t pid;

    struct sigaction act_p, act_c;

    act_p.sa_handler = do_sig_parent;
    sigemptyset(&act_p.sa_mask);
    act_p.sa_flags = 0;

    act_c.sa_handler = do_sig_child;
    sigemptyset(&act_c.sa_mask);
    act_c.sa_flags = 0;

    sigaction(SIGUSR1, &act_p, NULL);
    sigaction(SIGUSR2, &act_c, NULL);

    pid = fork();

    while (1) {
        if (pid > 0) {
            sleep(1);
            kill(pid, SIGUSR2);
            waitpid(pid, NULL, 0);
        } else if (pid == 0) {
            sleep(1);
            pid_t ppid = getppid();
            kill(ppid, SIGUSR1);
        }
    }

    return 0;
}