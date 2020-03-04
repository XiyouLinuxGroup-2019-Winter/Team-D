#include<stdio.h>
int main()
{
    char ch;
    int i=0;
    while((ch=getchar())!=EOF)
    i++;
    printf("%d\n",i);
}
