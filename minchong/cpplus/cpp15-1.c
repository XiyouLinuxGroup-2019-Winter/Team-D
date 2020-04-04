#include<stdio.h>
#include<string.h>
int main()
{
    char *pb="01001001";
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
    printf("%d\n",s);
}
