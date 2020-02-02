#include<stdio.h>
int fun(char a)
{
    if('A'<=a&&a<='Z') return a-'A'+1;
    else if('a'<=a&&a<='z') return a-'a'+1;
    else return -1;
}
int main ()
{
    char a;
    while(scanf("%c",&a)!=EOF)
    {
        getchar();
        printf("%d\n",fun(a));
    }
}

