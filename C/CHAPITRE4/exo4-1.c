#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define BUFFER_SIZE 512

int main()
{
    int pipe_word[2];
    int pipe_result[2];
    char line[BUFFER_SIZE] , word[BUFFER_SIZE];
    __pid_t pid;

    pipe(pipe_word);
    pipe(pipe_result);

    pid = fork();

    if(pid == 0)
    {
        int result;
        close(pipe_word[0]);
        close(pipe_result[1]);
        printf("Entrer le mot a chercher : ");
        fgets(word, BUFFER_SIZE, stdin);
        word[strcspn(word, "\n")] = 0;
        write(pipe_word[1], word, strlen(word) + 1);
        close(pipe_word[1]);

        read(pipe_result[0], &result, sizeof(result));
        if(result > 0)
        {
            printf("Le mot '%s' a été trouvé %d fois.\n", word, result);
        }
        else
        {
            printf("Le mot '%s' n'a pas été trouvé.\n", word);
        }
        close(pipe_result[0]);

        return 0;
    }

    close(pipe_word[1]);
    close(pipe_result[0]);
    read(pipe_word[0], word, BUFFER_SIZE);
    close(pipe_word[0]);

    FILE *file = fopen("/home/andrianina/S3/SYS_ADMIN/PROG_SYS/C/CHAPITRE2/exo2-1.c", "r");
    if(file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    while(fgets(line, BUFFER_SIZE, file))
    {
        char *token = strtok(line, " \t\n");
        while(token != NULL)
        {
            if(strcmp(token, word) == 0)
            {
                int count = 1;
                write(pipe_result[1], &count, sizeof(count));
                close(pipe_result[1]);
                fclose(file);
                return 0;
            }
            token = strtok(NULL, " \t\n");
        }
    }
    int count = 0;
    write(pipe_result[1], &count, sizeof(count));
    close(pipe_result[1]);
    fclose(file);
    return 0;
}