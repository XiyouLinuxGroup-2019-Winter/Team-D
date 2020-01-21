#include<stdio.h>
int main()
{
    int m,n;
    for(m=0;m<7;m++)
    {
        for(n=0;n<m;n++)
        printf("%c",'F'-n);
        printf("\n");
    }
}
