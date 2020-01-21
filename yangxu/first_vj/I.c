#include<stdio.h>
int main ()
{
    int n,i,k,f=0,m=0;
    int a[1000];
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++){
        if(a[i]<=k) f++;
        else{
            m=1;
            break;
        }
    }
    for(i=n-1;i>=0;i--){
        if(a[i]<=k) f++;
        else break;
    }
    if(m==0) f=n;
    printf("%d",f);
}

