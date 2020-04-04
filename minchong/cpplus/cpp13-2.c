#include<stdio.h>
#include<stdlib.h>
int main()
{
    char ch,str1[100],str2[100];
    FILE *fp,*cp;
    scanf("%s   %s",str1,str2);
    fp=fopen(str1,"rb");
    cp=fopen(str2,"wb+");
    while((ch=getc(fp))!=EOF)
        putc(ch,cp);
    fclose(fp);
    fclose(cp);
}
