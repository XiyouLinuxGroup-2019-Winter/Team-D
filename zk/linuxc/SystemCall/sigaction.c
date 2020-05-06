#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void do_sig(int num) {
    int n = 5;
    printf("I am do_sig function\n");
    while (n--) {
        printf("num = %d\n", num);
        sleep(1);
    }
}

int main() {
    struct sigaction act;

    act.sa_handler = do_sig;
//    act.sa_handler = SIG_DFL; 默认
//    act.sa_handler = SIG_IGN; 忽略
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);

    while (1) {
        printf("****\n");
        sleep(1);
    }
    return 0;
}