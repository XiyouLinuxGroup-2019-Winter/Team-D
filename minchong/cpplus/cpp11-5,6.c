#include<stdio.h>
#include<string.h>
char *f(char *str,char st)
{
    char *p;
    while(*str!='\0')
    {
        if(*str==st)
        {
            p=str;
            return p;
        }
        str++;
    }
    return NULL;
}
int main()
{
    char ch;
    char str[11]={"qwertyuioq"};
    while(1)
    {
        ch=getchar();
        if(ch=='&')
        break;
        if((f(str,ch))!=NULL)
        printf("%p  %c\n",f(str,ch),*f(str,ch));
        else
        printf("404,Not Fond!\n");
}
}
