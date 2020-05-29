#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex1, mutex2;
int v1, v2;

void *thread_func1(void *arg) {
    pthread_mutex_lock(&mutex1);
    v1 = 2;
    printf("t1拿到了mutex1这把锁\n");
    pthread_mutex_lock(&mutex2); // 阻塞, 死锁
    printf("t1拿到了mutex2这把锁\n");
    v2 = 200;
    int c = v1 + v2;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

void *thread_func2(void *arg) {
    pthread_mutex_lock(&mutex2);
    v2 = 3;
    printf("t2拿到了mutex2这把锁\n");
    pthread_mutex_lock(&mutex1); // 阻塞, 死锁
    printf("t2拿到了mutex1这把锁\n");
    v1 = 100;
    int c = v1 + v2;
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_create(&tid1, NULL, thread_func1, NULL);
    pthread_create(&tid2, NULL, thread_func2, NULL);
    while (1) {
        printf("sleeping\n");
        sleep(1);
    }
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&mutex2);
    return 1;
}