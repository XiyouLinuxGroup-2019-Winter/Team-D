#include<stdio.h>
int main ()
{
    int i,j,n;
    char a,b;
    scanf("%c",&a);
    n=a-'A'+1;
    for(i=1;i<=n;i++){
        b='A';
        for(j=1;j<=n-i;j++) printf(" ");
        for(j=1;j<=2*i-1;j++){
            if(j<i){
                printf("%c",b);
                b++;
            }
            if(j==i){
                printf("%c",b);
                b--;
            }
            if(j>i){
                printf("%c",b);
                b--;
            }
        }
        printf("\n");
    }
}

