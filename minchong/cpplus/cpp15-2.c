#include<stdio.h>
#include<string.h>
#include<limits.h>
int bio(char *);
char *f(int ,char *);
int main()
{
    char str1[100],str2[100],st[sizeof(int)+1];
    scanf("%s %s",str1,str2);
    int m,n;
    m=bio(str1);
    n=bio(str2);
    puts(f(~m,st));
    puts(f(~n,st));
    puts(f(m&n,st));
    puts(f(m|n,st));
    puts(f(m^n,st));
}
int bio(char * pb)
{
    int m,i=0,s=0,h=1,k;
    m=strlen(pb);
    for(m--;m;m--)
    {
        if(i==0)
        h=1;
        else
        {
            for(k=1;k<=i;k++)
            h*=2;
        }
        s+=(pb[m]-'0')*h;
        i++;
        h=1;
    }
    return s;
}
char *f(int m,char * st)
{
    int size=sizeof(int),i,k=m;
    for(i=size-1;i>=0;i--,k>>=1)
    st[i]=(1&k)+'0';
    st[size]='\0';
    return st;
}
