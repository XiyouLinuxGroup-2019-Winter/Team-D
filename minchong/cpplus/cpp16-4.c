#include<stdio.h>
#include<time.h>
#include<unistd.h>
int main()
{
    clock_t op=0,ed=0;
    op=clock();
    sleep(10);
    ed=clock();
    printf("%ld  %ld",op,ed);
    double s;
    op=(double)op;
    ed=(double)ed;
    s=(ed-op)/CLOCKS_PER_SEC;
    printf("%lf\n",s);
}
