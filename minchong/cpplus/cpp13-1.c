#include<stdio.h>
#include<stdlib.h>
int main()
{
    int ch;
    FILE *fp;
    char str[100];
    unsigned long s=0;
    scanf("%s",str);
    if((fp=fopen(str,"r"))==NULL)
    exit(EXIT_FAILURE);
    while((ch=getc(fp))!=EOF)
    {
        putc(ch,stdout);
        s++;
    }
    fclose(fp);
    printf("%ld  ",s);
    return 0;
}
