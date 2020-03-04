#include<stdio.h>
int main()
{
    char ch,c;
    int i=0;
    while((ch=getchar())!=EOF)
    {
        if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')
        i++;
        else
        {
            if(c>='a'&&c<='z'||c>='A'&&c<='Z')
            printf("%d  ",i);
            i=0;
        }
        c=ch;
    }
}
