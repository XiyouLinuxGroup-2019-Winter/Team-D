#include<stdio.h>
int main()
{
    struct box
    {
        unsigned int id : 8;
        unsigned int sz : 7;
        unsigned int dj : 2;
        unsigned int jc : 1;
        unsigned int xt : 1;
    };
    struct box init={1,1,1,1,1};
    printf("%d %d %d %d %d %p %p\n",init.id,init.sz,init.dj,init.jc,init.xt,&init.id,&init.sz);
}
