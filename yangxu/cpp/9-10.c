#include<stdio.h>
void fun(int a,int b)
{
    if(a<b){
        printf("%d",a);
    }else {
        fun(a/b,b);
        printf("%d",a%b);
    }
}
int main ()
{
    int a,b;
    scanf("%d %d",&a,&b);
    fun(a,b);
}

