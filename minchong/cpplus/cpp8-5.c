#include<stdio.h>
int main()
{
    char ch,ck;
    int i=50,k=0,m=100;
    printf("The number is 50. Is it right(Y/N)?");
    scanf("%c",&ch);
    ck=getchar();
    while (ch!='Y'&&ch!='y')
    {
        printf("Ok, the number you chosen is bigger or smaller than I guest?(B/S)");
        scanf("%c",&ch);
        ck=getchar();
        if (ch=='B'||ch=='b')
        {
            k=i;
            i=(m+k)/2;
        }
        else
        {
            m=i;
            i=(m+k)/2;
        }
        printf("The number is %d, Is it right(Y/N)?\n",i);
        scanf("%c",&ch);
        ck=getchar();
    }
    printf("GOOD!\n");
}
