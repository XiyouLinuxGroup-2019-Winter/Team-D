#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void printsigset(const sigset_t *set) {
    for (int i = 1; i < 32; ++i) {
        if (sigismember(set, i) == 1) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    putchar('\n');
}

int main() {
    sigset_t s, p;
    int i = 0;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigaddset(&s, SIGQUIT);
    sigaddset(&s, SIGKILL);
    sigaddset(&s, SIGSTOP);
    sigprocmask(SIG_BLOCK, &s, NULL);
    while (1) {
        sigpending(&p);
        printsigset(&p);
        if (i == 10) {
            sigdelset(&s, SIGINT);
            sigprocmask(SIG_UNBLOCK, &s, NULL);
        }
        sleep(1);
        i++;
    }
    return 0;
}