#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc , char* argv[])
{
    char* arg[] = {"emacs" , argv[1] , NULL};
    execv("/usr/bin/emacs" , arg);
}
