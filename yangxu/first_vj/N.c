#include<stdio.h>
int main ()
{
    int a[32][32]={0};
    a[0][1]=1;
    int n,i,j;
    while(~scanf("%d",&n)){
        printf("1\n");
        for(i=1;i<n;i++){
            for(j=1;j<=i+1;j++){
                a[i][j]=a[i-1][j-1]+a[i-1][j];
                if(j==1) printf("%d",a[i][j]);
                else printf(" %d",a[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

