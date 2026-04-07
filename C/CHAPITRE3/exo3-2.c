#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc , char* argv[])
{
    char* command;
    char* pwd = getenv("PWD");
    command = malloc(512 * sizeof(char));
    sprintf(command , "cp -r %s %s",pwd, argv[1]);

    system(command);
    return(0);
}