#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *th_fun(void *arg) {
    int n = 10;
    while (n--) {
        printf("thread ID = %lu, n = %d\n", pthread_self(), n);
        sleep(1);
    }
    return (void *) 1;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr; // 局部变量, attr里面的值是垃圾值
    int err;

    pthread_attr_init(&attr); // attr里面保存创建线程的默认属性
    // int detachstate : PTHREAD_CREATE_DETACHED PTHREAD_CREATE_JOINABLE
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&tid, &attr, th_fun, NULL);
    err = pthread_join(tid, NULL);

    if (err != 0) {
        printf("%s\n", strerror(err));
        pthread_exit((void *) 1);
    }
}
