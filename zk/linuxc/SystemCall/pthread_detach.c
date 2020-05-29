#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

void *thr_fn(void *arg) {
    int n = 3;
    while (n--) {
        printf("thread count %d\n", n);
        sleep(1);
    }
    return (void *)1;
}

int main() {
    pthread_t tid;
    void *tret;
    int err;

    pthread_create(&tid, NULL, thr_fn, NULL);
    pthread_detach(tid);

    while (1) {
        err = pthread_join(tid, &tret);
        if (err != 0) {
            fprintf(stderr, "thread %s\n", strerror(err));
        } else {
            fprintf(stdout, "thread exit code %d\n", (int)tret);
        }
        sleep(1);
    }
    return 0;
}