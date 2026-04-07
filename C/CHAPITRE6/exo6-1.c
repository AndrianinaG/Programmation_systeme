#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define SEUIL (1024 * 1024)   

void lister_repertoire(const char *chemin) 
{
    DIR *dir = opendir(chemin);
    if (dir == NULL) 
    {
        perror(chemin);
        return;
    }

    printf("=== Répertoire : %s ===\n", chemin);

    struct dirent *entree;
    int trouve = 0;

    while ((entree = readdir(dir)) != NULL) {
        if (strcmp(entree->d_name, ".")  == 0 || strcmp(entree->d_name, "..") == 0) 
        {
            continue;
        }

        /* Construction du chemin complet */
        char chemin_complet[4096];
        snprintf(chemin_complet, sizeof(chemin_complet), "%s/%s", chemin, entree->d_name);

        struct stat info;
        if (stat(chemin_complet, &info) == -1) 
        {
            perror(chemin_complet);
            continue;
        }

        /* On ne traite que les fichiers réguliers */
        if (!S_ISREG(info.st_mode)) 
        {
            continue;
        }

        if (info.st_size > SEUIL) 
        {
            printf("  %s  taille : %10lld octets  UID : %u\n",entree->d_name,(long long)info.st_size,(unsigned int)info.st_uid);
            trouve = 1;
        }
    }

    if (!trouve) 
    {
        printf("  (aucun fichier > 1 Mio)\n");
    }

    printf("\n");
    closedir(dir);
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        fprintf(stderr, "Usage : %s <répertoire1> [répertoire2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int i;
    for (i = 1; i < argc; i++) {
        lister_repertoire(argv[i]);
    }

    return EXIT_SUCCESS;
}