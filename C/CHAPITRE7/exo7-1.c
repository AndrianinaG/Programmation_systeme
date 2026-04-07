#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/* Calcul sans fin effectué par le fils */
void calcul_infini() 
{
    long long i = 0;
    while (1) 
    {
        i++;
        if (i % 100000000LL == 0) 
        {
            printf("[fils  PID=%d] compteur = %lld\n", getpid(), i);
            fflush(stdout);
        }
    }
}

int main() 
{
    pid_t pid_fils;
    int choix;

    pid_fils = fork();

    if (pid_fils < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    /* --- Processus fils --- */
    if (pid_fils == 0) 
    {
        sleep(3);  // Laisser le temps au père de s'installer
        calcul_infini();
        exit(EXIT_SUCCESS);
    }

    /* --- Processus père --- */
    printf("Père (PID=%d) — Fils créé (PID=%d)\n", getpid(), pid_fils);
    printf("------------------------------------------\n");
    printf("  s  →  Endormir le fils   (SIGSTOP)\n");
    printf("  r  →  Redémarrer le fils (SIGCONT)\n");
    printf("  q  →  Tuer le fils et quitter\n");
    printf("------------------------------------------\n");

    while (1) 
    {
        printf("\nVotre choix [s/r/q] : ");
        fflush(stdout);

        choix = getchar();

        /* Vider le tampon d'entrée (consommer le '\n' restant) */
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choix) 
        {
            case 's':
                if (kill(pid_fils, SIGSTOP) == 0)
                    printf("[père] Fils endormi (SIGSTOP).\n");
                else
                    perror("kill SIGSTOP");
                break;

            case 'r':
                if (kill(pid_fils, SIGCONT) == 0)
                    printf("[père] Fils redémarré (SIGCONT).\n");
                else
                    perror("kill SIGCONT");
                break;

            case 'q':
                if (kill(pid_fils, SIGKILL) == 0) 
                {
                    printf("[père] Fils tué (SIGKILL).\n");
                    waitpid(pid_fils, NULL, 0);
                } else 
                {
                    perror("kill SIGKILL");
                }
                printf("[père] Fin du programme.\n");
                exit(EXIT_SUCCESS);

            case EOF:
                printf("[père] EOF détecté, arrêt.\n");
                kill(pid_fils, SIGKILL);
                waitpid(pid_fils, NULL, 0);
                exit(EXIT_FAILURE);

            default:
                printf("Touche inconnue '%c'. Utilisez s, r ou q.\n", choix);
        }
    }

    return 0;
}