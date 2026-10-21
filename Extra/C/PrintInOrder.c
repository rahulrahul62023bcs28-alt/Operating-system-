#include <stdlib.h>
#include <semaphore.h>

typedef struct {
    sem_t a, b;
} Foo;

Foo* fooCreate() {
    Foo *obj = malloc(sizeof(Foo));
    sem_init(&obj->a, 0, 0);
    sem_init(&obj->b, 0, 0);
    return obj;
}

void first(Foo* obj, void (*printFirst)()) {
    printFirst();
    sem_post(&obj->a);
}

void second(Foo* obj, void (*printSecond)()) {
    sem_wait(&obj->a);
    printSecond();
    sem_post(&obj->b);
}

void third(Foo* obj, void (*printThird)()) {
    sem_wait(&obj->b);
    printThird();
}

void fooFree(Foo* obj) {
    sem_destroy(&obj->a);
    sem_destroy(&obj->b);
    free(obj);
}
