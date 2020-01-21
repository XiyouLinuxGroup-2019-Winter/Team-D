#include<stdio.h>
int main()
{
    float m;
    char name[20];
    printf("请输入身高和姓名：");
    scanf("%f %s",&m,name);
    printf("%s,you are %f feet tall",name,m);
}
