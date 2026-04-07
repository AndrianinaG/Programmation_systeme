#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAILLE_MAX 10

// Structure TypeTableau
struct TypeTableau {
    int tableau[TAILLE_MAX];
    int nb_elements;
    int integer_x;
};

// ─────────────────────────────────────────
// Thread 1 : génère le tableau aléatoire
// ─────────────────────────────────────────
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

// ─────────────────────────────────────────
// Thread 2 : recherche x dans le tableau
// ─────────────────────────────────────────
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

    // ── Lancer Thread 1 (génération du tableau) ──
    if (pthread_create(&thread_generation, NULL, generer_tableau, &data) != 0) 
    {
        fprintf(stderr, "Erreur : création du thread de génération échouée.\n");
        return EXIT_FAILURE;
    }
    pthread_join(thread_generation, NULL);
    // ── Thread principal : lire x pendant que Thread 1 tourne ──
    printf("[Main] Entrez un entier x à rechercher : ");
    fflush(stdout);
    scanf("%d", &data.integer_x);
    printf("[Main] Génération terminée. Recherche de x = %d...\n", data.integer_x);


    // ── Attendre la fin de la génération ──

    // ── Lancer Thread 2 (recherche de x) ──
    if (pthread_create(&thread_recherche, NULL, rechercher_x, &data) != 0) 
    {
        fprintf(stderr, "Erreur : création du thread de recherche échouée.\n");
        return EXIT_FAILURE;
    }

    // ── Récupérer le résultat de Thread 2 ──
    long resultat;
    pthread_join(thread_recherche, (void **)&resultat);

    // ── Afficher le résultat ──
    if (resultat == 1)
        printf("[Main] Résultat : %d EST dans le tableau. (retour = 1)\n", data.integer_x);
    else
        printf("[Main] Résultat : %d N'EST PAS dans le tableau. (retour = 0)\n", data.integer_x);

    return EXIT_SUCCESS;
}