#include "header.h"

int main()
{
    key_t key;
    int shmid;
    int semid;
    int i;
    struct SharedData *data;

    key = getkey();

    shmid = shmget(key, sizeof(struct SharedData), 0666);

    if(shmid == -1)
    {
        perror("shmget failed");
        return 1;
    }

    data = (struct SharedData *)shmat(shmid, NULL, 0);

    if(data == (void *)-1)
    {
        perror("shmat failed");
        return 1;
    }

    semid = semget(key, 2, 0666);

    if(semid == -1)
    {
        perror("semget failed");
        return 1;
    }

    wait_sem(semid, READY);

    for(i = 0; i < data->n; i++)
    {
        data->square[i] = data->num[i] * data->num[i];
    }

    printf("Consumer: Squaring completed.\n");

    signal_sem(semid, DONE);

    while(1)
    {
        pause();
    }

    return 0;
}
