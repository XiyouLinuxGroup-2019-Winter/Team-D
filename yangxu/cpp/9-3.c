#include<stdio.h>
void fun(char a,int i,int j)
{
    int m,n;
    for(m=0;m<i;m++){
        for(n=0;n<j;n++){
            printf("%c",a);
        }
        printf("\n");
    }
}
int main ()
{
    char a;
    int i,j;
    scanf("%c %d %d",&a,&i,&j);
    fun(a,i,j);
}

