#include<stdio.h>
int main ()
{
    int a=0,n=0;
    char b;
    while(b=getchar()){
        switch(b){
            case '#': n=1;
                      break;
            case '.': printf("!");
                      a++;
                      break;
            case '!': printf("!!");
                      a++;
                      break;
            default: printf("%c",b);
        }
        if(n==1) break;
    }
    printf("\n%d\n",a);
}

