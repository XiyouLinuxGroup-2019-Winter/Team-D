#include<stdio.h>
#include<string.h>
int main ()
{
    char a[82];
    scanf("%s",a);
    int i,n=strlen(a);
    for(i=n-1;i>=0;i--){
        printf("%c",a[i]);
    }
}

