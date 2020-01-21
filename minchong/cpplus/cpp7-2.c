#include<stdio.h>
int main()
{
    char po;
    int w=0;
    while(1)
    {
        scanf("%c",&po);
        if(po=='#')
        break;
        if(w%8!=0||w==0)
        {
            printf("%c-%d ",po,po);
            w++;
        }
        else
        {
            printf("\n");
            printf("%c-%d ",po,po);
            w++;
        }

    }
}
