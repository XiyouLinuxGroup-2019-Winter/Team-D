#include<stdio.h>
int main ()
{
    int a=0;
    char b;
    while(b=getchar()){
        if(b=='#') break;
        else if(b=='.'){
            printf("!");
            a++;
        }
        else if(b=='!'){
            printf("!!");
            a++;
        }else printf("%c",b);
    }
    printf("\n%d\n",a);
}

