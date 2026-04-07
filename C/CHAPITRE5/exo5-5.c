#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/* Compteur global et mutex associé */
int compt = 0;
int limite = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Thread 1 : incrémente le compteur, attend entre 1 et 5 secondes */
void *thread_incrementeur(void *arg) 
{
    srand(time(NULL));

    while (1) {
        pthread_mutex_lock(&mutex);
        compt++;
        printf("[Thread 1] Compteur incrémenté → %d\n", compt);
        int atteint;
        if (compt >= limite)
            atteint = 1;
        else
            atteint = 0;
        pthread_mutex_unlock(&mutex);

        if (atteint) break;

        int attente = 1 + rand() % 5;   /* entre 1 et 5 secondes */
        sleep(attente);
    }

    printf("[Thread 1] Limite atteinte, fin.\n");
    return NULL;
}

/* Thread 2 : affiche le compteur toutes les 2 secondes */
void *thread_afficheur(void *arg) {
    while (1) {
        sleep(2);

        pthread_mutex_lock(&mutex);
        int valeur = compt;
        int atteint;
        if (compt >= limite)
            atteint = 1;
        else
            atteint = 0;
        pthread_mutex_unlock(&mutex);

        printf("[Thread 2] Valeur actuelle du compteur : %d\n", valeur);

        if (atteint) break;
    }

    printf("[Thread 2] Limite atteinte, fin.\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <limite>\n", argv[0]);
        return EXIT_FAILURE;
    }

    limite = atoi(argv[1]);
    if (limite <= 0) {
        fprintf(stderr, "La limite doit être un entier strictement positif.\n");
        return EXIT_FAILURE;
    }

    printf("Démarrage — limite fixée à %d\n\n", limite);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_incrementeur, NULL);
    pthread_create(&t2, NULL, thread_afficheur, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("\nProgramme terminé. Valeur finale du compteur : %d\n", compt);
    return EXIT_SUCCESS;
}