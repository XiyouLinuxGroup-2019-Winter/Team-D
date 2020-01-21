#include<stdio.h>
int main()
{
    int m,n,i,s;
    char k;
    printf("请输入大写字母：");
    scanf("%c",&k);
    s=k-'A'+2;
    for(m=0;m<s;m++)
    {
        for(n=0;n<s-m;n++)
        printf(" ");
        for(i=0;i<m;i++)
        printf("%c",'A'+i);
        for(i=1;i<m;i++)
        printf("%c",'A'+m-i-1);
        for(n=0;n<s-m;n++)
        printf(" ");
        printf("\n");
    }
}
