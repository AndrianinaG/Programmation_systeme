#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    __pid_t pid_fork = fork();

    if (pid_fork == -1)
    {
        perror("Problème dans fork()\n");
        exit(-1);
    }
    
    else if (pid_fork == 0)
    {
        printf("Je suis le fils\n");
    }
    else
    {
        printf("Je suis le père\n");
        wait(NULL);
    }
    
    
    
}