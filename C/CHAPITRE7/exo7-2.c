#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int n, i;

    // Saisie de la taille
    printf("Entrez la taille du tableau : ");
    scanf("%d", &n);

    // Allocation dynamique
    int *tab = (int *)malloc(n * sizeof(int));

    if (tab == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return 1;
    }

    // Saisie des elements
    printf("Entrez les %d elements du tableau :\n", n);
    for (int j = 0; j < n; j++) 
    {
        printf("  tab[%d] = ", j);
        scanf("%d", tab + j);  // utilisation des pointeurs
    }

    // Saisie de l'indice avec verification
    do 
    {
        printf("Entrez un indice i : ");
        scanf("%d", &i);

        if (i < 0 || i >= n) {
            printf("Indice invalide ! Reessayez.\n");
        }

    } while (i < 0 || i >= n);

    // Affichage
    printf("tab[%d] = %d\n", i, *(tab + i));

    // Liberation memoire
    free(tab);

    return 0;
}