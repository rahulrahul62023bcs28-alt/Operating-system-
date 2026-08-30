#include "header.h"

int main()
{
    key_t key;
    int shmid;
    int semid;
    int i;
    struct SharedData *data;
    union semun u;

    key = getkey();

    shmid = shmget(key, sizeof(struct SharedData), IPC_CREAT | 0666);

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

    semid = semget(key, 2, IPC_CREAT | 0666);

    if(semid == -1)
    {
        perror("semget failed");
        return 1;
    }

    u.val = 0;
    semctl(semid, READY, SETVAL, u);

    u.val = 0;
    semctl(semid, DONE, SETVAL, u);

    printf("Enter the number of elements to square: ");
    scanf("%d", &data->n);

    printf("Enter %d elements:\n", data->n);

    for(i = 0; i < data->n; i++)
    {
        scanf("%d", &data->num[i]);
    }

    printf("\nProducer: Data stored in shared memory.\n");

    signal_sem(semid, READY);

    wait_sem(semid, DONE);

    printf("\nProducer: Results\n");

    for(i = 0; i < data->n; i++)
    {
        printf("%d square = %d\n",
               data->num[i], data->square[i]);
    }

    while(1)
    {
        pause();
    }

    return 0;
}
