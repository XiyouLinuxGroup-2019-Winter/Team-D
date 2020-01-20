#include<stdio.h>
#include<string.h>
char a[100000];
int main ()
{
    int i;
    while(scanf("%s",a)){
        if(strlen(a)==1&&a[0]=='0') break;
        for(i=strlen(a)-1;i>=0;i--){
            a[i+2]=a[i];
        }
        a[0]=a[1]='0';
        for(i=strlen(a)-1;i>=1;i--){
            if((a[i]+a[i-1]-2*'0')>=10){
                a[i-2]++;
                a[i-1]=(a[i]+a[i-1]-2*'0')%10+'0';
                a[i]=10;
            }else {
                a[i-1]=a[i]+a[i-1]-'0';
                a[i]=10;
            }
        }
        for(i=0;i<2;i++) printf("%c",a[i]);
        memset(a,0,sizeof(char)*10000);
        //printf("%d",strlen(a));
    }
 }

