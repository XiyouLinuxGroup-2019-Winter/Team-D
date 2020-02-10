#include<stdio.h>
int main ()
{
    int i,j,n;
    scanf("%d %d",&i,&j);
    for(n=i;n<=j;n++){
        printf("%5d %5d %5d\n",n,n*n,n*n*n);
    }
}

