#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100

double tableau[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_lissage(void *arg) {
    while (1) {
        double temp[N];

        pthread_mutex_lock(&mutex);

        temp[0]    = tableau[0];      
        temp[N-1]  = tableau[N-1];

        int i;
        for (i = 1; i <= N-2; i++) {
            temp[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        }

        for (i = 0; i < N; i++) {
            tableau[i] = temp[i];
        }

        printf("[Thread 1] Passe de lissage effectuée.\n");

        pthread_mutex_unlock(&mutex);

        int attente;
        if ((rand() % 3) == 0)
            attente = 1;
        else if ((rand() % 3) == 1)
            attente = 2;
        else
            attente = 3;

        sleep(attente);
    }

    return NULL;
}

void *thread_affichage(void *arg) {
    int passe = 0;

    while (1) {
        sleep(4);

        pthread_mutex_lock(&mutex);

        passe++;
        printf("\n[Thread 2] --- État du tableau (affichage n°%d) ---\n", passe);

        int i;
        for (i = 0; i < N; i++) {
            printf("  tableau[%2d] = %7.3f", i, tableau[i]);
            if ((i + 1) % 4 == 0)
                printf("\n");
        }
        printf("\n");

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void) {
    srand((unsigned int)time(NULL));

    tableau[0]   = 0.0;
    tableau[N-1] = 0.0;

    int i;
    for (i = 1; i <= N-2; i++) {
        tableau[i] = (double)rand() / RAND_MAX * 100.0;
    }

    printf("[Main] Tableau initialisé (tableau[0]=0, tableau[99]=0).\n\n");

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_lissage,   NULL);
    pthread_create(&t2, NULL, thread_affichage, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}
