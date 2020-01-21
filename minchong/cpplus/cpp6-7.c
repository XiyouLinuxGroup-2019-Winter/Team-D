#include<stdio.h>
#include<string.h>
int main()
{
    int i,m;
    char p[50];
    scanf("%s",p);
    m=strlen(p);
    for(i=m-1;i>=0;i--)
    printf("%c",p[i]);
    printf("\n");
}
