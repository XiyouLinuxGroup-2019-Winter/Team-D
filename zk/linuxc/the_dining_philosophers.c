#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 4
/**
 * 最多允许4个哲学家吃饭, 第5个想吃要阻塞直到有1个哲学家吃完
 */
pthread_mutex_t chops[5];
sem_t max_philosopher_num;

void think(int i) {
    printf("I am thinking %d\n", i);
    sleep(rand() % 3);
}

void hungry(int i) {
    printf("I am hungry %d\n", i);
    sleep(rand() % 3);
}

void eat(int i) {
    printf("I am eating %d\n", i);
    sleep(rand() % 3);
}

void *philosopher(void *arg) {
    int i = (int) arg;
    think(i);
    hungry(i);

    sem_wait(&max_philosopher_num);
    pthread_mutex_lock(&chops[i]);
    pthread_mutex_lock(&chops[(i + 1) % 5]);

    eat(i);

    pthread_mutex_unlock(&chops[i]);
    pthread_mutex_unlock(&chops[(i + 1) % 5]);
    sem_post(&max_philosopher_num);

    return NULL;
}

int main() {
    pthread_t tid[5];
    srand(time(NULL));

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_init(&chops[i], NULL);
    }
    sem_init(&max_philosopher_num, 0, NUM);

    for (int i = 0; i < 5; ++i) {
        pthread_create(&tid[i], NULL, philosopher, (void *) i);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(tid[i], NULL);
    }
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_destroy(&chops[i]);
    }

    sem_destroy(&max_philosopher_num);
    return 0;
}