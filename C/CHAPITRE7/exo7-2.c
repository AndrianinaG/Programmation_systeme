#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int n, i;

    printf("Entrez la taille du tableau : ");
    scanf("%d", &n);

    int *tab = (int *)malloc(n * sizeof(int));

    if (tab == NULL) 
    {
        printf("Erreur d'allocation memoire.\n");
        return 1;
    }

    printf("Entrez les %d elements du tableau :\n", n);
    for (int j = 0; j < n; j++) 
    {
        printf("  tab[%d] = ", j);
        scanf("%d", tab + j);  
    }

    do 
    {
        printf("Entrez un indice i : ");
        scanf("%d", &i);

        if (i < 0 || i >= n) {
            printf("Indice invalide ! Reessayez.\n");
        }

    } while (i < 0 || i >= n);

    printf("tab[%d] = %d\n", i, *(tab + i));

    free(tab);

    return 0;
}
