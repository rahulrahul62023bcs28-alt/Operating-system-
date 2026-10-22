// Q5. Building H2O — LeetCode 1117
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int h, o, inside, finished;
} H2O;

H2O* h2oCreate() {
    H2O *obj = calloc(1, sizeof(H2O));
    pthread_mutex_init(&obj->mutex, NULL);
    pthread_cond_init(&obj->cond, NULL);
    return obj;
}

void hydrogen(H2O* obj, void (*releaseHydrogen)()) {
    pthread_mutex_lock(&obj->mutex);
    while (obj->h == 2 || obj->inside == 3)
        pthread_cond_wait(&obj->cond, &obj->mutex);
    obj->h++;
    obj->inside++;
    pthread_cond_broadcast(&obj->cond);
    while (obj->inside < 3)
        pthread_cond_wait(&obj->cond, &obj->mutex);
    pthread_mutex_unlock(&obj->mutex);
    releaseHydrogen();
    pthread_mutex_lock(&obj->mutex);
    obj->finished++;
    if (obj->finished == 3) {
        obj->h = obj->o = obj->inside = obj->finished = 0;
        pthread_cond_broadcast(&obj->cond);
    }
    pthread_mutex_unlock(&obj->mutex);
}

void oxygen(H2O* obj, void (*releaseOxygen)()) {
    pthread_mutex_lock(&obj->mutex);
    while (obj->o == 1 || obj->inside == 3)
        pthread_cond_wait(&obj->cond, &obj->mutex);
    obj->o++;
    obj->inside++;
    pthread_cond_broadcast(&obj->cond);
    while (obj->inside < 3)
        pthread_cond_wait(&obj->cond, &obj->mutex);
    pthread_mutex_unlock(&obj->mutex);
    releaseOxygen();
    pthread_mutex_lock(&obj->mutex);
    obj->finished++;
    if (obj->finished == 3) {
        obj->h = obj->o = obj->inside = obj->finished = 0;
        pthread_cond_broadcast(&obj->cond);
    }
    pthread_mutex_unlock(&obj->mutex);
}

void h2oFree(H2O* obj) {
    pthread_mutex_destroy(&obj->mutex);
    pthread_cond_destroy(&obj->cond);
    free(obj);
}
