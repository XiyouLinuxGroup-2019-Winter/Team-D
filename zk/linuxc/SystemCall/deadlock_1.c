#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *thread_func(void *arg) {
    int n = 10;
    while (n--) {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex); // 死锁
        printf("hello\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid, NULL, thread_func, NULL);
    int n = 10;
    while (n--) {
        pthread_mutex_lock(&mutex);
        printf("HELLO\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_join(tid, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}