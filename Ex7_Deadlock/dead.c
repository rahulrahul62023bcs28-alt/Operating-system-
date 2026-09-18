#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int detectSafety(int m, int n, int avail[],
                 int max[m][n], int alloc[m][n])
{
    int need[MAX][MAX];
    int work[MAX];
    int finish[MAX] = {0};
    int safeSeq[MAX];
    int i, j, count = 0, found;

    /* Calculate Need = Max - Allocation */
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];

            if (need[i][j] < 0)
            {
                printf("\nInvalid input: Allocation > Max\n");
                return 0;
            }
        }
    }

    /* Work = Available */
    for (j = 0; j < n; j++)
        work[j] = avail[j];

    /* Safety Algorithm */
    while (count < m)
    {
        found = 0;

        for (i = 0; i < m; i++)
        {
            if (finish[i] == 0)
            {
                int possible = 1;

                /* Check Need[i] <= Work */
                for (j = 0; j < n; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if (possible)
                {
                    /* Work = Work + Allocation */
                    for (j = 0; j < n; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    /* Check whether all processes can finish */
    if (count == m)
    {
        printf("\nSystem is in SAFE state.\n");

        printf("Safe Sequence: ");
        for (i = 0; i < m; i++)
        {
            printf("P%d", safeSeq[i]);

            if (i != m - 1)
                printf(" -> ");
        }

        printf("\n");
        return 1;
    }
    else
    {
        printf("\nSystem is in UNSAFE state.\n");
        return 0;
    }
}


int processResourceReq(int m, int n, int req[m][n],
                       int avail[], int max[m][n],
                       int alloc[m][n])
{
    int need[MAX][MAX];
    int i, j;
    int process;

    printf("\nEnter process number for resource request (0 to %d): ", m - 1);
    scanf("%d", &process);

    if (process < 0 || process >= m)
    {
        printf("Invalid process number.\n");
        return 0;
    }

    /* Calculate Need */
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    /* Step 1: Request <= Need */
    for (j = 0; j < n; j++)
    {
        if (req[process][j] > need[process][j])
        {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return 0;
        }
    }

    /* Step 2: Request <= Available */
    for (j = 0; j < n; j++)
    {
        if (req[process][j] > avail[j])
        {
            printf("\nResources are not available.\n");
            printf("Process P%d must WAIT.\n", process);
            return 0;
        }
    }

    /* Step 3: Pretend to allocate resources */
    for (j = 0; j < n; j++)
    {
        avail[j] -= req[process][j];
        alloc[process][j] += req[process][j];
    }

    /* Step 4: Check whether new state is safe */
    printf("\nChecking the new state...\n");

    if (detectSafety(m, n, avail, max, alloc))
    {
        printf("Request can be GRANTED to P%d.\n", process);
        return 1;
    }
    else
    {
        /* Rollback */
        for (j = 0; j < n; j++)
        {
            avail[j] += req[process][j];
            alloc[process][j] -= req[process][j];
        }

        printf("Request CANNOT be granted.\n");
        printf("Request is denied and system state is restored.\n");

        return 0;
    }
}


int main()
{
    int m, n;
    int i, j;

    int avail[MAX];
    int max[MAX][MAX];
    int alloc[MAX][MAX];
    int req[MAX][MAX];

    printf("===== BANKER'S ALGORITHM =====\n");

    printf("\nEnter number of processes: ");
    scanf("%d", &m);

    printf("Enter number of resource types: ");
    scanf("%d", &n);

    /* Input Allocation Matrix */
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < m; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < n; j++)
            scanf("%d", &alloc[i][j]);
    }

    /* Input Maximum Matrix */
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < m; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < n; j++)
            scanf("%d", &max[i][j]);
    }

    /* Input Available */
    printf("\nEnter Available Resources:\n");
    for (j = 0; j < n; j++)
        scanf("%d", &avail[j]);

    /* Display Need Matrix */
    printf("\nNeed Matrix (Max - Allocation):\n");

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", max[i][j] - alloc[i][j]);
        }

        printf("\n");
    }

    /* Check current system safety */
    printf("\n===== SAFETY CHECK =====\n");

    detectSafety(m, n, avail, max, alloc);

    /* Resource Request */
    printf("\n===== RESOURCE REQUEST =====\n");

    printf("Enter Resource Request Matrix:\n");

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            req[i][j] = 0;
        }
    }

    printf("Enter request for the selected process:\n");

    /* Process number is selected inside function */
    for (j = 0; j < n; j++)
    {
        scanf("%d", &req[0][j]);
    }

    /*
       req[0] temporarily stores the request.
       Copy it to the selected process after getting process number.
    */

    {
        int process;
        int tempReq[MAX];

        printf("Enter process number again for request (0 to %d): ", m - 1);
        scanf("%d", &process);

        if (process >= 0 && process < m)
        {
            for (j = 0; j < n; j++)
                tempReq[j] = req[0][j];

            for (j = 0; j < n; j++)
                req[process][j] = tempReq[j];

            processResourceReq(m, n, req, avail, max, alloc);
        }
        else
        {
            printf("Invalid process number.\n");
        }
    }

    return 0;
}

\*             BANKER'S ALGORITHM
                     |
          -------------------------
          |                       |
    SAFETY ALGORITHM       RESOURCE REQUEST
          |                       |
 Need = Max - Allocation    Request <= Need ?
          |                       |
 Work = Available           Request <= Available ?
          |                       |
 Find Need <= Work          Pretend Allocation
          |                       |
 Work = Work + Allocation   Run Safety Algorithm
          |                       |
 Safe Sequence              Safe → GRANT
          |                 Unsafe → ROLLBACK
    Safe / Unsafe  

===== BANKER'S ALGORITHM =====

Enter number of processes: 5
Enter number of resource types: 3

Enter Allocation Matrix:
P0: 0 1 0
P1: 2 0 0
P2: 3 0 2
P3: 2 1 1
P4: 0 0 2

Enter Maximum Matrix:
P0: 7 5 3
P1: 3 2 2
P2: 9 0 2
P3: 2 2 2
P4: 4 3 3

Enter Available Resources:
3 3 2

Need Matrix (Max - Allocation):
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1

===== SAFETY CHECK =====

System is in SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2

===== RESOURCE REQUEST =====
Enter Resource Request Matrix:
Enter request for the selected process:
1 0 2
Enter process number again for request (0 to 4): 1

Enter process number for resource request (0 to 4): 1

Checking the new state...

System is in SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2
Request can be GRANTED to P1.

	*/
