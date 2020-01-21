#include<stdio.h>
#include<string.h>
int main ()
{
    char s[100];
    scanf("%s",s);
    int i,f=0,n;
    while(1)
    {
        for(i=0;i<strlen(s)/2;i++){
            if(s[i]!=s[strlen(s)-1-i]) f=1;
        }
        if(strlen(s)==1) break;
        if(f==1) break;
        else s[strlen(s)-1]='\0';
    }
    if(strlen(s)==1) n=0;
    else n=strlen(s);
    printf("%d",n);
}

