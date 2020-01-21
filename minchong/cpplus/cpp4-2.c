#include<stdio.h>
int main()
{
    char name[20];
    printf("请输入姓名：");
    scanf("%s",name);
    printf("%20s\n",name);
    printf("%-20s\n",name);
    printf("   %s   ",name);
}
