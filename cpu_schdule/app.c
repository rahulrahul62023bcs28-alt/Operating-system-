#include "header.h"

int main()
{
    int id[10], run[10];
    int n, i, ch;

    printf("CPU Scheduling\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Round Robin\n");

    printf("\nEnter your choice: ");
    scanf("%d", &ch);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        id[i] = i + 1;

        printf("Enter Burst Time for P%d: ", id[i]);
        scanf("%d", &run[i]);
    }

    if(ch == 1)
    {
        fcfs(id, run, n);
    }
    else if(ch == 2)
    {
        sjf(id, run, n);
    }
    else if(ch == 3)
    {
        rr(id, run, n);
    }
    else
    {
        printf("Invalid Choice\n");
    }

    return 0;
}
