#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main()
{
    char ch,str1[100],ct,*kp;
    FILE *fp,*op;
    int m,i=0,h;
    scanf("%s",str1);
    fp=fopen(str1,"r");
    fseek(fp,0L,SEEK_END);
    m=ftell(fp);
    fseek(fp,0L,SEEK_SET);
    kp=(char *)malloc(m+10);
    while((ch=getc(fp))!=EOF)
    {
        kp[i]=toupper(ch);
         i++;
    }
    fclose(fp);
    op=fopen(str1,"wt++");
    for(h=0;h<=i;h++)
    putc(kp[h],op);
    fclose(op);               
}
