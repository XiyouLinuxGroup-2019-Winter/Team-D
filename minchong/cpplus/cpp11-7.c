#include<stdio.h>
#include<string.h>
char *f(char *str1,char *str2,int n)
{
    int s1=strlen(str1)-1,s2=strlen(str2),i;
    for(i=0;i<n;i++)
    {
        if(i==s2)
        {
        str1[s1+i]='\0';
            break;
        }
        str1[s1+i]=str2[i];
    }
    return str1;
}
int main()
{
    char str1[100],str2[100];
    int n;
    while(1)
    {
        fgets(str1,100,stdin);
        fgets(str2,100,stdin);
        scanf("%d",&n);
        if(n==0)
        break;
        puts(f(str1,str2,n));
    }
}
