#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAILLE_MAX 10

struct TypeTableau {
    int tableau[TAILLE_MAX];
    int nb_elements;
    int integer_x;
};

void *generer_tableau(void *arg) {
    struct TypeTableau *data = (struct TypeTableau *)arg;

    printf("[Thread 1] Génération de %d éléments aléatoires...\n", data->nb_elements);

    for (int i = 0; i < data->nb_elements; i++) 
    {
        data->tableau[i] = rand() % 100;
    }

    printf("[Thread 1] Tableau généré : [");
    for (int i = 0; i < data->nb_elements; i++) 
    {
        printf("%d", data->tableau[i]);
        if (i < data->nb_elements - 1) 
        {
            printf(", ");
        }
    }
    printf("]\n");

    pthread_exit(NULL);
}

void *rechercher_x(void *arg) {
    struct TypeTableau *data = (struct TypeTableau *)arg;
    long resultat = 0;

    for (int i = 0; i < data->nb_elements; i++) 
    {
        if (data->tableau[i] == data->integer_x) 
        {
            resultat = 1;
            break;
        }
    }

    pthread_exit((void *)resultat);
}

int main() {
    pthread_t thread_generation, thread_recherche;
    srand(time(NULL));

    struct TypeTableau data;
    data.nb_elements = TAILLE_MAX;

    if (pthread_create(&thread_generation, NULL, generer_tableau, &data) != 0) 
    {
        fprintf(stderr, "Erreur : création du thread de génération échouée.\n");
        return EXIT_FAILURE;
    }
    pthread_join(thread_generation, NULL);
    printf("[Main] Entrez un entier x à rechercher : ");
    fflush(stdout);
    scanf("%d", &data.integer_x);
    printf("[Main] Génération terminée. Recherche de x = %d...\n", data.integer_x);

    if (pthread_create(&thread_recherche, NULL, rechercher_x, &data) != 0) 
    {
        fprintf(stderr, "Erreur : création du thread de recherche échouée.\n");
        return EXIT_FAILURE;
    }

    long resultat;
    pthread_join(thread_recherche, (void **)&resultat);

    if (resultat == 1)
        printf("[Main] Résultat : %d EST dans le tableau. (retour = 1)\n", data.integer_x);
    else
        printf("[Main] Résultat : %d N'EST PAS dans le tableau. (retour = 0)\n", data.integer_x);

    return EXIT_SUCCESS;
}
