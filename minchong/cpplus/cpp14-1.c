#include<stdio.h>
#include<string.h>
struct mon
{
    char month[4];
    int days;
    int num;
};
struct mon mons[12]=
{
    {"Jan", 31, 1},
    {"Feb", 28, 2},
    {"Mar", 31, 3},
    {"Apr", 30, 4},
    {"May", 31, 5},
    {"Jun", 30, 6},
    {"Jul", 31, 7},
    {"Aug", 31, 8},
    {"Sep", 30, 9},
    {"Oct", 31, 10},
    {"Nov", 30, 11},
    {"Dec", 31, 12}
};
int main()
{
    char name[4];
    int i,s=0;
    scanf("%s",name);
    for(i=0;;i++)
    {
        s+=mons[i].days;
        if((strcmp(name,mons[i].month))==0)
        break;
    }
    printf("%d\n",s);
}
