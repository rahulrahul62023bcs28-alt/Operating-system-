//Program 2: Two-way communication using two pipes (String Validation)

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
    int fd1[2], fd2[2];
    pid_t pid;
    char str[100], result[20];
    int i, len;
    int digit = 0, special = 0;

    if(pipe(fd1) == -1 || pipe(fd2) == -1)
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

    if(pid > 0)
    {
        close(fd1[0]);
        close(fd2[1]);

        printf("Parent: Enter a string: ");
        scanf("%s", str);

        if(write(fd1[1], str, sizeof(str)) == -1)
        {
            perror("Write failed");
            return 1;
        }

        if(read(fd2[0], result, sizeof(result)) == -1)
        {
            perror("Read failed");
            return 1;
        }

        printf("Parent: %s\n", result);

        close(fd1[1]);
        close(fd2[0]);

        wait(NULL);
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);

        if(read(fd1[0], str, sizeof(str)) == -1)
        {
            perror("Read failed");
            return 1;
        }

        len = strlen(str);

        for(i = 0; i < len; i++)
        {
            if(str[i] >= '0' && str[i] <= '9')
                digit = 1;

            if((str[i] >= 33 && str[i] <= 47) ||
               (str[i] >= 58 && str[i] <= 64) ||
               (str[i] >= 91 && str[i] <= 96) ||
               (str[i] >= 123 && str[i] <= 126))
                special = 1;
        }

        if(digit && special && len > 7)
            strcpy(result, "Valid");
        else
            strcpy(result, "Invalid");

        if(write(fd2[1], result, sizeof(result)) == -1)
        {
            perror("Write failed");
            return 1;
        }

        close(fd1[0]);
        close(fd2[1]);
    }

    return 0;
}

/*Output:
Parent: Enter a string: Rahul@123
Parent: Valid

Parent: Enter a string: Rahul
Parent: Invalid */
