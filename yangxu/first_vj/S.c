#include<stdio.h>
int main ()
{
    int n,i,j,y;
    int a[10005]={0};
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(a[j]>a[j+1]){
                y=a[j];
                a[j]=a[j+1];
                a[j+1]=y;
            }
        }
    }
    if(n%2!=0) printf("%d",a[n/2]);
    else printf("%d",a[n/2-1]);
}

