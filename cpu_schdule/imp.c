#include "header.h"

void display(int id[], int run[], int wait[], int turn[], int n)
{
    int i;
    float avgw = 0, avgt = 0;

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n", id[i], run[i], wait[i], turn[i]);

        avgw = avgw + wait[i];
        avgt = avgt + turn[i];
    }

    avgw = avgw / n;
    avgt = avgt / n;

    printf("\nAverage Waiting Time = %.2f\n", avgw);
    printf("Average Turnaround Time = %.2f\n", avgt);
}

void fcfs(int id[], int run[], int n)
{
    int wait[10], turn[10];
    int i;

    wait[0] = 0;

    for(i = 1; i < n; i++)
    {
        wait[i] = wait[i - 1] + run[i - 1];
    }

    for(i = 0; i < n; i++)
    {
        turn[i] = wait[i] + run[i];
    }

    display(id, run, wait, turn, n);
}

void sjf(int id[], int run[], int n)
{
    int wait[10], turn[10];
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(run[i] > run[j])
            {
                temp = run[i];
                run[i] = run[j];
                run[j] = temp;

                temp = id[i];
                id[i] = id[j];
                id[j] = temp;
            }
        }
    }

    wait[0] = 0;

    for(i = 1; i < n; i++)
    {
        wait[i] = wait[i - 1] + run[i - 1];
    }

    for(i = 0; i < n; i++)
    {
        turn[i] = wait[i] + run[i];
    }

    display(id, run, wait, turn, n);
}

void rr(int id[], int run[], int n)
{
    int left[10], wait[10], turn[10];
    int tm = 0, done, i;

    for(i = 0; i < n; i++)
    {
        left[i] = run[i];
        wait[i] = 0;
    }

    do
    {
        done = 1;

        for(i = 0; i < n; i++)
        {
            if(left[i] > 0)
            {
                done = 0;
                left[i]--;
                tm++;

                if(left[i] == 0)
                {
                    turn[i] = tm;
                    wait[i] = turn[i] - run[i];
                }
            }
        }

    } while(done == 0);

    display(id, run, wait, turn, n);
}
