#include<stdio.h>
int main ()
{
    int a=0;
    char b,n;
    while(b=getchar()){
        if(b=='#') break;
        if(n=='e'&&b=='i') a++;
        n=b;
    }
    printf("%d\n",a);
}

