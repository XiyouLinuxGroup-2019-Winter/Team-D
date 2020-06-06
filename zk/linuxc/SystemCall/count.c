#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NLOOP 5000

int count;

void *doit(void *vptr);

int main() {
    pthread_t tidA, tidB;

    pthread_create(&tidA, NULL, doit, NULL);
    pthread_create(&tidB, NULL, doit, NULL);

    // wait for both threads to terminate
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    return 0;
}

void *doit(void *vptr) {
    int i, val;
    // 临界区: 锁住的范围
    for (i = 0; i < NLOOP; ++i) {
        // 谁要操作全局资源count谁拿锁, 锁只有一把
        // 拿锁
        val = count;
        printf("thread ID = %lu: %d\n", pthread_self(), val + 1);
        count = val + 1;
        // 解锁
    }
    return NULL;
}