//Program 1: Child sends a number through a pipe, Parent checks whether it is a power of 3

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int isPowerOfThree(int n)
{
    if(n <= 0)
        return 0;

    while(n % 3 == 0)
        n = n / 3;

    return (n == 1);
}

int main()
{
    int fd[2];
    pid_t pid;
    int number;

    if(pipe(fd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();

    if(pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    if(pid == 0)
    {
        close(fd[0]);

        printf("Child: Enter a number: ");
        scanf("%d",&number);

        if(write(fd[1], &number, sizeof(number)) == -1)
        {
            perror("Write failed");
            return 1;
        }

        close(fd[1]);
    }
    else
    {
        close(fd[1]);

        if(read(fd[0], &number, sizeof(number)) == -1)
        {
            perror("Read failed");
            return 1;
        }

        close(fd[0]);

        wait(NULL);

        printf("Parent: Received Number = %d\n", number);

        if(isPowerOfThree(number))
            printf("Parent: %d is a Power of 3\n", number);
        else
            printf("Parent: %d is NOT a Power of 3\n", number);
    }

    return 0;
}

/*Output:
Child: Enter a number: 27
Parent: Received Number = 27
Parent: 27 is a Power of 3

Child: Enter a number: 20
Parent: Received Number = 20
Parent: 20 is NOT a Power of 3 */
