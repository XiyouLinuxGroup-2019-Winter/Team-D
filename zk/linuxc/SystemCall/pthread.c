#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *th_func(void *arg) {
    int *p = (int *)arg;
    printf("thread PID = %d\n", getpid());
    printf("thread ID = %lu\n", pthread_self());
    printf("thread *arg = %d\n", *p);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t tid;
    int n = 10;

    pthread_create(&tid, NULL, th_func, (void *)&n);
    printf("main thread ID = %lu\n", pthread_self());
    printf("main child thread ID = %lu\n", tid);
    printf("main PID = %d\n", getpid());
    sleep(3);
    return 0;
}