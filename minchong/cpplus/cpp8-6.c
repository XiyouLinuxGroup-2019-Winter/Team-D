#include<stdio.h>
#include<ctype.h>
char get_first(void)
{
    int ch;
    while (!isalpha(ch=getchar()))
        ;
    return ch;
}
int main()
{
    printf("%c\n",get_first());
}
