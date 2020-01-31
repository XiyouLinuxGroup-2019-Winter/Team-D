#include<stdio.h>
int main ()
{
    int a=0;
    char b;
    while(b=getchar()){
        if(b=='#') break;
        a++;
    }
    getchar();
    printf("%d",a);
}

