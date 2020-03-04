#include<stdio.h>
int main()
{
    char ch=0;
    int n;
    while((ch=getchar())!=EOF)
    {
        n++;
        if(ch<' ')
        {
            if(ch=='\t')
            {
                putchar('\\');
                putchar('t');
            }
            else if(ch=='\n')
            {
                putchar('\\');
                putchar('n');
            }
            else
            {
                putchar('^');
                putchar(ch+64);
            }
        }
        else
        putchar(ch);
        if(n%10==0)
        printf("\n");
    }
}
