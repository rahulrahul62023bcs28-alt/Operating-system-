
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int n, i, sum = 0, evenSum = 0, oddSum = 0;
    pid_t pid1, pid2;

    printf("Enter n: ");
    scanf("%d", &n);

    for(i = 1; i <= n; i++)
        sum += i;

    printf("A : Sum of first %d natural numbers = %d\n", n, sum);

    pid1 = fork();

    if(pid1 < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if(pid1 == 0)
    {
        for(i = 2; i <= n; i += 2)
            evenSum += i;

        printf("B : Sum of Even Numbers = %d\n", evenSum);
    }
    else if(pid1 > 0)
    {
        pid2 = fork();

        if(pid2 < 0)
        {
            perror("fork failed");
            return 1;
        }
        else if(pid2 == 0)
        {
            for(i = 1; i <= n; i += 2)
                oddSum += i;

            printf("C : Sum of Odd Numbers = %d\n", oddSum);
        }
        else if(pid2 > 0)
        {
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
/*         A (Sum of n numbers)
       / \
      B   C
   (Even) (Odd)  */
