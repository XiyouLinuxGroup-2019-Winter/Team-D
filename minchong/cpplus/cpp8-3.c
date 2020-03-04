#include<stdio.h>
#include<ctype.h>
int main()
{
    char ch;
    int i=0,n=0;
    while((ch=getchar())!=EOF)
    {
        if (islower(ch))
            i++;
        else if (isupper(ch))
            n++;
    }
    printf("%d  %d\n",i,n);
}
