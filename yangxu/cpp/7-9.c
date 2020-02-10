#include<stdio.h>
int main ()
{
    int a,i,j,f;
    scanf("%d",&a);
//  if(a>=2) printf("2 ");
    for(i=2;i<=a;i++){
        f=0;
        for(j=2;j<i;j++){
            if(i%j==0) f=1;
        }
        if(f==0) printf("%d ",i);
    }
}

