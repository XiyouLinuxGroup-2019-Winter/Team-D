#include<stdio.h>
void f(int m[][5],int n,int h)
{
    int i, k;
    for(i=0;i<n;i++)
    for(k=0;k<h;k++)
    {
        printf("%d  ",*(*(m+i)+k));
        *(*(m+i)+k)*=2;
    }
}
int main()
{
    int m[3][5]={1,2,3,4,5,6,7,8,9,0,1,2,1,2,1};
    f(m,3,5);
}
