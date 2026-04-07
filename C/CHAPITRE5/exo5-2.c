#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAILLE 10

void *generer_tableau(void *arg) 
{
    int *tableau = malloc(TAILLE * sizeof(int));
    
    for (int i = 0; i < TAILLE; i++) 
    {
        tableau[i] = rand() % 100;
    }
    // Retourner le tableau via pthread_exit

    pthread_exit((void *)tableau);
}

int main() {
    pthread_t thread;
    int *tableau_recu = NULL;

    srand(time(NULL));

    if (pthread_create(&thread, NULL, generer_tableau, NULL) != 0) 
    {
        fprintf(stderr, "Erreur : impossible de créer le thread.\n");
        return EXIT_FAILURE;
    }

    // Récupérer le tableau retourné par le thread
    if (pthread_join(thread, (void **)&tableau_recu) != 0) 
    {
        fprintf(stderr, "Erreur : pthread_join échoué.\n");
        return EXIT_FAILURE;
    }

    // Afficher le tableau dans le thread principal
    if (tableau_recu != NULL) 
    {
        printf("Tableau reçu du thread : [");
        for (int i = 0; i < TAILLE; i++) {
            printf("%d", tableau_recu[i]);
            if (i < TAILLE - 1)
                printf(", ");
        }
        printf("]\n");

        // Libérer la mémoire allouée par le thread
        free(tableau_recu);
    }

    printf("Fin du programme.\n");
    return EXIT_SUCCESS;
}