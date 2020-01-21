#include<stdio.h>
#include<string.h>
int main()
{
    char a[82];
    char b[82];
    int n,m;
    printf("请您输入名\n");
    scanf("%s",a);
    printf("请您输入姓\n");
    scanf("%s",b);
    printf("%s %s\n",a,b);
    n=strlen(a);
    m=strlen(b);
    printf("%*.d %*.d\n",n,n,m,m);
    printf("%s %s\n",a,b);
    printf("%-*.d %-*.d\n",n,n,m,m);
}

