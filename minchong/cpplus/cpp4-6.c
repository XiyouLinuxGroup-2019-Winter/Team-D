#include<stdio.h>
#include<string.h>
int main()
{
    int q,w;
    char m[20],n[20];
    printf("请输入名：");
    scanf("%s",m);
    printf("请输入姓：");
    scanf("%s",n);
    q=strlen(m);
    w=strlen(n);
    printf("%s %s\n",m,n);
    printf("%d %d",q,w);
}
