#include<stdio.h>
#include<string.h>
int main ()
{
    int n,i,k=0;
    char a[1000];
    scanf("%d",&n);
    while(n--){
        k=0;
        scanf("%s",a);
        for(i=0;i<strlen(a);i++){
            if('0'<=a[i]&&a[i]<='9') k++;
        }
        printf("%d\n",k);
    }
}

