#include<stdio.h>
int main ()
{
    int i;
    double a[8],b[8];
    for(i=0;i<8;i++) scanf("%lf",&a[i]);
    for(i=0;i<8;i++){
        if(i==0) b[i]=a[i];
        else b[i]=a[i]+b[i-1];
    }
    for(i=0;i<8;i++) printf("%-10f",a[i]);
    printf("\n");
    for(i=0;i<8;i++) printf("%-10f",b[i]);
}

