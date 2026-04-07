#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *tableau;
    int taille;
} Params;

void *afficher_tableau(void *arg) {
    Params *params = (Params *)arg;

    printf("Tableau affiché par le thread : [");
    for (int i = 0; i < params->taille; i++) 
    {
        printf("%d", params->tableau[i]);
        if (i < params->taille - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    int tableau[] = {10, 20, 30, 40, 50};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    Params params;
    params.tableau = tableau;
    params.taille  = taille;

    if (pthread_create(&thread, NULL, afficher_tableau, &params) != 0) 
    {
        fprintf(stderr, "Erreur : impossible de créer le thread.\n");
        return EXIT_FAILURE;
    }

    pthread_join(thread, NULL);

    printf("Thread terminé. Fin du programme.\n");
    return EXIT_SUCCESS;
}