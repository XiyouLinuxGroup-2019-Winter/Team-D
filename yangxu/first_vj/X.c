#include<stdio.h>
int main ()
{
    int n,i,f=0,max,min;
    int a[100005];
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    max=a[0];
    min=a[0];
    for(i=0;i<n;i++){
        if(a[i]>max) max=a[i];
        if(a[i]<min) min=a[i];
    }
    for(i=0;i<n;i++){
        if(a[i]!=max&&a[i]!=min) f++;
    }
    printf("%d",f);
}

