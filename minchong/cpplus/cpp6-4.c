#include<stdio.h>
int main()
{
    int m,n,s=0;
    for(m=0;m<7;m++)
    {
        for(n=0;n<m;n++)
        {
        printf("%c",'A'+s);
        s++;
        }
        printf("\n");
    }
}
