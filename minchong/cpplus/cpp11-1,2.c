#include<stdio.h>
#include<string.h>
char *pf(char *k,int n)
{
    int i=0;
    do
    {
        k[i]=getchar();
        i++;
    }
    while(i<n&&k[i-1]!=' '&&k[i-1]!='\t'&&k[i-1]!='\n');
    k[i]='\0';
    return k;
}
int main()
{
    char str[100];
    puts(pf(str,11));
}
