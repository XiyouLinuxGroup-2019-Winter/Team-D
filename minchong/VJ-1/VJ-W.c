#include<stdio.h>
int main()
{
    int m,n,num1[10000],h,num2[10000],num3[10000],q,w,e,k,i;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
    scanf("%d",&num1[i]);
    for(i=0,h=10;i<m;h*=10,i++)
    {
    for(k=0;k<n;k++)
    {
        num2[k]=(num1[k]%h)/(h/10);
    }
    for(q=0;q<n;q++)
        for(w=q+1;w<n;w++)
        if(num2[q]<num2[w])
        {
            e=num2[q];
            num2[q]=num2[w];
            num2[w]=e;
        }
    for(q=0;q<n;q++)
    if(num2[q]!=num2[q+1])
        break;
    for(w=0;w<q;w++)
        num3[w]=num3[w]||1;
    }
    for(i=0;i<n;i++)
    printf("%d",num3[i]);
}
