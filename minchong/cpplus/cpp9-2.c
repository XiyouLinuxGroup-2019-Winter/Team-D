#include<stdio.h>
void chline(char ch,int j,int i)
{
    int m,n;
    for(m=0;m<j;m++)
    {
        for(n=0;n<i;n++)
        putchar(ch);
        printf("\n");
    }
}
int main()
{
    char ch;
    int j,i;
    scanf("%c %d %d",&ch,&j,&i);
    chline(ch,j,i);
}
