#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/**
 * 如果想给某个哲学家筷子，就将他需要的所有资源都给他，然后让他进餐，否则就一个都不给他。
 */

pthread_mutex_t mutex, chops[5];

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
    int i = (int)arg;

    think(i);
    hungry(i);

    pthread_mutex_lock(&mutex); // 阻止其他线程拿筷子
    pthread_mutex_lock(&chops[i]);
    pthread_mutex_lock(&chops[(i + 1) % 5]);
    pthread_mutex_unlock(&mutex);

    eat(i);

    pthread_mutex_unlock(&chops[i]);
    pthread_mutex_unlock(&chops[(i + 1) % 5]);
    return NULL;
}

int main() {
    pthread_t tid[5];
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_init(&chops[i], NULL);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_create(&tid[i], NULL, philosopher, (void *)i);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_destroy(&chops[i]);
    }

    return 0;
}
