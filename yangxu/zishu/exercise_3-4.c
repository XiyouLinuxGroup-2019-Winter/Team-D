#include<stdio.h>
#include<string.h>
int fun(char a[82],int n)
{
    int f=0;
    for(int i=0;i<n;i++){
        for(int j=i+n;j<strlen(a);j=j+n){
            if(a[i]!=a[j]) f=1;
        }
        if(f==1) break;
    }
    return f;
}
int main ()
{
    char a[82];
    scanf("%s",a);
    int f=0;
    for(int i=1;i<=strlen(a)/2;i++){
        if(!fun(a,i)){
            printf("%d\n",i);
            f=1;
            break;
        }
    }
    if(f==0) printf("非周期字符串\n");
}

