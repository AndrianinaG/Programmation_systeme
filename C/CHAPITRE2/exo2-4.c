#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include<errno.h>
int main() 
{
    pid_t pid1, pid2;
    time_t debut, fin;

    debut = time(NULL);
    pid1 = fork();
    
    if (pid1 < 0) 
    {
        perror("fork fils 1");
        exit(EXIT_FAILURE);
    }
    
    if (pid1 == 0) 
    {
        srand(time(NULL) + getpid());
        int duree = (rand() % 10) + 1;  
        printf("Fils 1 (PID = %d) : je vais dormir %d seconde(s).\n", getpid(), duree);
        sleep(duree);
        printf("Fils 1 (PID = %d) : je me réveille après %d seconde(s).\n", getpid(), duree);
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
        srand(time(NULL) + getpid());
        int duree = (rand() % 10) + 1;  
        printf("Fils 2 (PID = %d) : je vais dormir %d seconde(s).\n", getpid(), duree);
        sleep(duree);
        printf("Fils 2 (PID = %d) : je me réveille après %d seconde(s).\n", getpid(), duree);
        exit(EXIT_SUCCESS);
    }

    printf("Père  (PID = %d) : j'attends la fin des deux fils...\n", getpid());

    wait(NULL);
    wait(NULL);

    fin = time(NULL);

    printf("\nPère  : les deux fils ont terminé.\n");
    printf("Durée totale (temps du fils le plus long) : %ld seconde(s).\n", (long)(fin - debut));

    return 0;
}
