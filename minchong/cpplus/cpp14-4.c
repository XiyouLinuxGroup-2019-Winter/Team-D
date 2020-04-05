#include<stdio.h>
#include<string.h>
struct mp
{
    char name[10];
    char ms[10];
    char mod[10];
};
struct soi
{
    char num[10];
    struct mp lk;
};
void print(struct soi *p)
{
    printf("%s , %s ,%s ,%s\n",p->lk.name,p->lk.ms,p->lk.mod,p->num);
}
int main()
{
    int i;
    struct soi p[5]=
    {
        {"302039823", {"Dribble", "FLossie", "M"}},
        {"302039824", {"Hello", "Kitty"}},
        {"302039285", {"Hello", "Jimmy", "J"}},
        {"302039286", {"Good", "Job"}},
        {"302039287", {"Jump", "High", "J"}}
    };
    for(i=0;i<5;i++)
    print(&p[i]);
}
