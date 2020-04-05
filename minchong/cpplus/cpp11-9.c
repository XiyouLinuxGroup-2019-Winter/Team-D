#include<stdio.h>
#include<string.h>
char *f(char *str)
{
    int n=strlen(str)-1,i;
    char ch;
    for(i=0;i<=n/2;i++)
    {
        ch=str[i];
        str[i]=str[n-i];
        str[n-i]=ch;
    }
    return str;
}
int main()
{
    char str[100];
    while((gets(str))!=EOF)
    {
        puts(f(str));
    }
}
