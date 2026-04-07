#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    bool answer = true;
    while (answer)
    {
        char* fichier = malloc(512 * sizeof(char));
        printf("Fichier à ouvrir (entrer q pour quitter): ");
        fgets(fichier , 512 , stdin);
        fichier[strcspn(fichier , "\n")] = '\0';
        if (strcmp(fichier , "q") == 0)
        {
            answer = false;
        }
        else
        {
            __pid_t pid = fork();
            if (pid == 0)
            {
                printf("Processus fils : %d\n", getpid());
                char* arg[] = {"emacs" , fichier , NULL};
                execv("/usr/bin/emacs" , arg);
            }
            wait(NULL);
        }
        QUESTION:
        printf("Voulez-vous continuer ?(y/n) : ");
        char reponse;
        scanf(" %c", &reponse);
        if (reponse == 'n')
        {
            answer = false;
        }
        else if (reponse != 'y' && reponse != 'n')
        {
            
            printf("Réponse invalide.\n");
            goto QUESTION;
        }
        getchar();
    }
}