#include<stdio.h>
void chline(char ch,int i,int j)
{
    int n,m;
    for(n=0;n<j;n++){
        for(m=0;m<i;m++){
            printf("%c ",ch);
        }
        printf("\n");
    }
}
int main ()
{
    char ch;
    int i,j;
    scanf("%c %d %d",&ch,&i,&j);
    chline(ch,i,j);
}

