#include<stdio.h>
int main ()
{
    int i,j;
    char a='F';
    for(i=0;i<6;i++){
        a='F';
        for(j=0;j<=i;j++){
            printf("%c",a);
            a--;
        }
        printf("\n");
    }
}

