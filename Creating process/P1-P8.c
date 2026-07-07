#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid2, pid3, pid4, pid5, pid6, pid7, pid8;

    pid2 = fork();

    if(pid2 < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if(pid2 == 0)
    {
        printf("P2 : PID = %d Parent = %d\n", getpid(), getppid());

        pid4 = fork();

        if(pid4 < 0)
        {
            perror("fork failed");
            return 1;
        }
        else if(pid4 == 0)
        {
            printf("P4 : PID = %d Parent = %d\n", getpid(), getppid());

            pid6 = fork();

            if(pid6 < 0)
            {
                perror("fork failed");
                return 1;
            }
            else if(pid6 == 0)
            {
                printf("P6 : PID = %d Parent = %d\n", getpid(), getppid());
            }
            else if(pid6 > 0)
            {
                wait(NULL);
            }
        }
        else if(pid4 > 0)
        {
            wait(NULL);
        }

        return 0;
    }
    else if(pid2 > 0)
    {
        wait(NULL);

        pid3 = fork();

        if(pid3 < 0)
        {
            perror("fork failed");
            return 1;
        }
        else if(pid3 == 0)
        {
            printf("P3 : PID = %d Parent = %d\n", getpid(), getppid());

            pid5 = fork();

            if(pid5 < 0)
            {
                perror("fork failed");
                return 1;
            }
            else if(pid5 == 0)
            {
                printf("P5 : PID = %d Parent = %d\n", getpid(), getppid());

                pid7 = fork();

                if(pid7 < 0)
                {
                    perror("fork failed");
                    return 1;
                }
                else if(pid7 == 0)
                {
                    printf("P7 : PID = %d Parent = %d\n", getpid(), getppid());
                    return 0;
                }
                else if(pid7 > 0)
                {
                    wait(NULL);

                    pid8 = fork();

                    if(pid8 < 0)
                    {
                        perror("fork failed");
                        return 1;
                    }
                    else if(pid8 == 0)
                    {
                        printf("P8 : PID = %d Parent = %d\n", getpid(), getppid());
                        return 0;
                    }
                    else if(pid8 > 0)
                    {
                        wait(NULL);
                    }
                }
            }
            else if(pid5 > 0)
            {
                wait(NULL);
            }

            return 0;
        }
        else if(pid3 > 0)
        {
            wait(NULL);
            printf("P1 : PID = %d Parent = %d\n", getpid(), getppid());
        }
    }

    return 0;
}

/* P1
├── P2
│   └── P4
│       └── P6
└── P3
    └── P5
        ├── P7
        └── P8. */

