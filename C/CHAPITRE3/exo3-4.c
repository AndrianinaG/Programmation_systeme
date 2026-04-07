#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int main()
{
    bool answer = true;

    while (answer)
    {
        char* rep;
        char* command;
        char* pwd = getenv("PWD");

        command = malloc(512 * sizeof(char));
        rep = malloc(512 * sizeof(char));

        printf("Chemin absolu du repertoire (entrer q pour quitter): ");
        fgets(rep , 512 , stdin);
        rep[strcspn(rep , "\n")] = '\0';

        if (strcmp(rep , "q") == 0)
        {
            answer = false;
        }

        sprintf(command , "cp -r %s %s",pwd,rep);
        system(command);
        printf("Repertoire copié dans %s\n",rep);
        QUESTION:
        printf("Voulez-vous continuer ?(y/n) : ");
        char reponse;
        scanf(" %c", &reponse);
        if (reponse == 'n')
        {
            answer = false;
        }
        else if (reponse != 'y' || reponse != 'n')
        {
            printf("Réponse invalide.\n");
            goto QUESTION;
        }
    }
    
}
