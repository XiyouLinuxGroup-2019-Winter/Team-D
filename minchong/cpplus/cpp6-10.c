#include<stdio.h>
int main()
{
    int m,n,s;
    while(1)
    {
        scanf("%d %d",&m,&n);
        if(n<=m)
        break;
        for(m;m<=n;m++)
        s+=(m*m);
        printf("%d\n",s);
    }
}
