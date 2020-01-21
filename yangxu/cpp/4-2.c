#include<stdio.h>
int main ()
{
    char a[82];
    printf("请您输入姓名(包含双引号)\n");
    scanf("%s",a);
    printf("%s\n",a);
    printf("%20s\n",a);
    printf("%-20s\n",a);
    printf("   %s\n",a);
}

