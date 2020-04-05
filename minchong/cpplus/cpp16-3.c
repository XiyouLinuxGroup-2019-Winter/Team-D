#include<stdio.h>
#include<math.h>
#include<stdlib.h>
struct j
{
    float l;
    float r;
};
struct z
{
    float x;
    float y;
};
struct z *f(struct j * p1,struct z *k)
{
    k->x=p1->l*cos(p1->r);
    k->y=p1->l*sin(p1->r);
    return k;
}
int main()
{
    struct z *k=(struct z *)malloc(sizeof(struct z));
    struct j *p=(struct j *)malloc(sizeof(struct j));
    scanf("%f %f",&p->l,&p->r);
    k=f(p,k);
    printf("%.2f %.2f\n",k->x,k->y);
}
