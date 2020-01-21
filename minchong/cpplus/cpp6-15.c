#include<stdio.h>
#include<string.h>
int main()
{
    char p[255];
    int m;
    scanf("%s",p);
    m=strlen(p);
    for(--m;m>=0;m--)
    printf("%c",p[m]);
}
