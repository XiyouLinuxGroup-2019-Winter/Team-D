#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
    double m,k;
    int l;
    l=atoi(argv[2]);
    m=atof(argv[1]);
    k=m*l;
    printf("%lf \n",k);
}
