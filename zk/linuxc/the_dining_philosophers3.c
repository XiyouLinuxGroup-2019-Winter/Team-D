#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t chops[5];

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

    if (i % 2 == 0) {
        pthread_mutex_lock(&chops[(i + 1) % 5]);
        pthread_mutex_lock(&chops[i]);
        eat(i);
        pthread_mutex_unlock(&chops[i]);
        pthread_mutex_unlock(&chops[(i + 1) % 5]);
    } else {
        pthread_mutex_lock(&chops[i]);
        pthread_mutex_lock(&chops[(i + 1) % 5]);
        eat(i);
        pthread_mutex_unlock(&chops[i]);
        pthread_mutex_unlock(&chops[(i + 1) % 5]);
    }

    return NULL;
}

int main() {
    pthread_t tid[5];
    srand(time(NULL));

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_init(&chops[i], NULL);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_create(&tid[i], NULL, philosopher, (void *)i);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_join(tid[i], NULL);
    }

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_destroy(&chops[i]);
    }

    return 0;
}