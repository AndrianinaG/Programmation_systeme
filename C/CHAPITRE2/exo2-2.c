#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<errno.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) 
    {
        perror("fork fils 1");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) 
    {
        printf("Je suis le fils 1 (PID = %d, PPID = %d)\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }

    pid2 = fork();

    if (pid2 < 0) 
    {
        perror("fork fils 2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) 
    {
        printf("Je suis le fils 2 (PID = %d, PPID = %d)\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    }
    printf("Je suis le père  (PID = %d)\n", getpid());

    wait(NULL);
    wait(NULL);

    printf("Le père : les deux fils ont terminé.\n");

    return 0;
}