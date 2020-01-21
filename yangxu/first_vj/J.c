#include<stdio.h>
int main ()
{
    int n,f,a,b,c=0,max;
    scanf("%d",&n);
    f=n;
    while(f--){
        scanf("%d %d",&a,&b);
        c=c+b-a;
        if(f==n-1) max=c;
        if(c>max) max=c;
    }
    printf("%d",max);
}

