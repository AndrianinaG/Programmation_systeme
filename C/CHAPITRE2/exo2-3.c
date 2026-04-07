#include <stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int i;

    for (i = 0; i < 5; i++) 
    {
        pid = fork();

        if (pid < 0) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            printf("Fils %d : PID = %d, PPID = %d\n", i + 1, getpid(), getppid());
            break;
        }
    }

    if (pid != 0) 
    {
        printf("Père  : PID = %d\n", getpid()); 
        for (i = 0; i < 5; i++) 
        {
            wait(NULL);
        }
        printf("Père  : tous les fils ont terminé.\n");
    }

    return 0;
}