// Q4. The Dining Philosophers — LeetCode 1226
#include <stdlib.h>
#include <semaphore.h>

typedef struct {
    sem_t room;
    sem_t fork[5];
} DiningPhilosophers;

DiningPhilosophers* diningPhilosophersCreate() {
    DiningPhilosophers *obj = malloc(sizeof(DiningPhilosophers));
    for (int i = 0; i < 5; i++) {
        sem_init(&obj->fork[i], 0, 1);
    }
    sem_init(&obj->room, 0, 4);
    return obj;
}

void wantsToEat(DiningPhilosophers* obj, int philosopher,
                void (*pickLeftFork)(), void (*pickRightFork)(),
                void (*eat)(), void (*putLeftFork)(), void (*putRightFork)()) {
    int l = philosopher;
    int r = (philosopher + 1) % 5;
    sem_wait(&obj->room);
    sem_wait(&obj->fork[l]);
    sem_wait(&obj->fork[r]);
    pickLeftFork();
    pickRightFork();
    eat();
    putLeftFork();
    putRightFork();
    sem_post(&obj->fork[r]);
    sem_post(&obj->fork[l]);
    sem_post(&obj->room);
}

void diningPhilosophersFree(DiningPhilosophers* obj) {
    for (int i = 0; i < 5; i++) {
        sem_destroy(&obj->fork[i]);
    }
    sem_destroy(&obj->room);
    free(obj);
}
