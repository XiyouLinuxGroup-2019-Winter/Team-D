#include<stdio.h>
#include<string.h>
char *f(char *str)
{
    char st[100];
    int i,m=strlen(str),h=0;
    for(i=0;i<=m;i++)
    {
       if(str[i]==' ')
        continue;
        st[h]=str[i];
        h++;
    }
    for(i=0;i<h;i++)
    str[i]=st[i];
    for(h;h<m;h++)
    str[h]='\0';
    return str;
}
int main()
{
    char str[110];
    while(1)
    {
        fgets(str,100,stdin);
        if(str[0]==' ')
        break;
        fputs(f(str),stdout);
    }
}
