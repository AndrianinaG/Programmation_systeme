#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];       
    pid_t pid;
    char fd_read_str[16];
    char fd_write_str[16];
    const char *message = "Bonjour depuis le programme père !\n";

    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
    {
        close(fd[1]);

        snprintf(fd_read_str,  sizeof(fd_read_str),  "%d", fd[0]);
        snprintf(fd_write_str, sizeof(fd_write_str), "%d", fd[1]);

        char *args[] = { "./fils", fd_read_str, fd_write_str, NULL };
        execv("./fils", args);

        perror("execv");
        exit(EXIT_FAILURE);

    } 
    else
    {
        close(fd[0]);

        printf("[Père] Envoi du message : %s", message);
        fflush(stdout);

        if (write(fd[1], message, strlen(message)) == -1) 
        {
            perror("write");
        }

        close(fd[1]);

        wait(NULL);
        printf("[Père] Programme fils terminé.\n");
    }

    return 0;
}
