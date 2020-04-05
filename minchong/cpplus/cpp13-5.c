#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE *fp, *op;
    char in[40],out[40],ch;
    int s=0;
    printf("Enter the file name:");
    gets(in);
    fp=fopen(in,"r");
    strncpy(out,in,35);
    out[35]='\0';
    strcat(out,".red");
    op=fopen(out, "w");
    while ((ch=getc(fp))!=EOF)
        if (s++%3==0)
            putc(ch,op);
}
