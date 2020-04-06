#include<stdio.h>
#include<string.h>
void f(char *str,int n)
{
    int i;
    char ch;
    for(i=0;;i++)
    {
        ch=getchar();
        if(i==0&&(ch==' '||ch=='\t'||ch=='\n'))
            i--;
        else if(i==n||ch==' '||ch=='\t'||ch=='\n')
        {
            str[i]='\0';
            break;
        }
        else
        str[i]=ch;
    }
}
int main()
{
    char str[100];
    f(str,10);
    puts(str);
}
