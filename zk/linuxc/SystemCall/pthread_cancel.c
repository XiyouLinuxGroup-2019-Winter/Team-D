#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *th_fun(void *arg) {
    int i = 0;
    int *p = (int *)arg;
    printf("thread PID = %d\n", getpid());
    printf("thread ID = %lu\n", pthread_self());
    printf("thread *arg = %d\n", *p);
    while (1) {
        i++;
        pthread_testcancel();
    }
}

int main() {
    pthread_t tid;
    int n = 10;

    pthread_create(&tid, NULL, th_fun, (void *)&n);
    printf("main thread ID = %lu\n", pthread_self());
    pthread_cancel(tid);
    while (1) {
        sleep(1);
    }
    return 0;
}