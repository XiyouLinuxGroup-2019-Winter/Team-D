#include<stdio.h>
int main ()
{
    int a,c=0;
    char b;
    while(b=getchar()){
        if(b=='#') break;
        a=b;
        printf("%c-%-5d",b,a);
        c++;
        if(c%8==0) printf("\n");
    }
    getchar();
}

