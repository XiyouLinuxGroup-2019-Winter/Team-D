#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_alarm(int signo) {

}

/**
 *
 * @param nsecs
 * @return 未睡够的秒数
 */
unsigned int mysleep(unsigned int nsecs) {
    struct sigaction newact, oldact;
    sigset_t newmask, oldmask, suspmask;
    unsigned int unslept;

    newact.sa_handler = sig_alarm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    alarm(nsecs);

    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM);
    sigsuspend(&suspmask);

    // alarm(0)返回未定时够的秒数, 如果定时够了返回0
    unslept = alarm(0);

    sigaction(SIGALRM, &oldact, NULL);
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;
}

int main() {
    while (1) {
        mysleep(2);
        printf("Two seconds passed\n");
    }
    return 0;
}