#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 0x100000

int print_ntimes(char *str) {
    printf("%s", str);
    sleep(1);
    return 0;
}

void *th_fun(void *arg) {
    int n = 3;
    while (n--) {
        print_ntimes("Hello World\n");
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int err, detachstate, i = 1;
    pthread_attr_t attr;
    size_t stacksize;
    void *stackaddr;

    pthread_attr_init(&attr);

    pthread_attr_getstack(&attr, &stackaddr, &stacksize);
    printf("stack address = %p\n", stackaddr);
    printf("stack size = %zx\n", stacksize);

    pthread_attr_getdetachstate(&attr, &detachstate);
    if (detachstate == PTHREAD_CREATE_DETACHED) {
        printf("thread detached\n");
    } else if (detachstate == PTHREAD_CREATE_JOINABLE) {
        printf("thread join\n");
    } else {
        printf("thread un known\n");
    }
    // 设置线程分离属性
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    while (1) {
        // 在堆上申请内存, 指定线程栈的起始地址和大小
        stackaddr = malloc(SIZE);  // 1M
        if (stackaddr == NULL) {
            perror("malloc");
            exit(1);
        }
        stacksize = SIZE;
        pthread_attr_setstack(&attr, stackaddr, stacksize);
        err = pthread_create(&tid, &attr, th_fun, NULL);
        if (err != 0) {
            printf("%s\n", strerror(err));
            exit(1);
        }
        printf("%d\n", i++);
    }

    // 销毁线程的属性占用的资源
    pthread_attr_destroy(&attr);
    return 0;
}