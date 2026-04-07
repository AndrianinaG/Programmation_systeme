#include<stdio.h>
#include<stdlib.h>

int main(int argc , char *argv[])
{
    int sum = 0 ;

    int nb1 = atoi(argv[1]);
    int nb2 = atoi(argv[2]);
    sum = nb1 + nb2;
    printf("%d + %d = %d\n",nb1 , nb2, sum);
    
    return 0;
}