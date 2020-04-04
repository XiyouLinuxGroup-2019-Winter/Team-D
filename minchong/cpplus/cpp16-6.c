#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct names
{
    char first[40];
    char last[40];
};
int comp(const void *p1,const void *p2)
{
    const struct names *ps1=(const struct names *)p1;
    const struct names *ps2=(const struct names *)p2;
    int res;
    res=strcmp(ps1->last,ps2->last);
    if(res!=0)
    return res;
    else
    return strcmp(ps1->first,ps2->first);
}
int main()
{
    struct names staff[5] =
	{
		{"Angle" , "Baby"} ,
		{"Michael" , "Jordan"},
		{"Michael" , "Jackson"},
		{"Bill" , "Gates"},
		{"Jackie" , "Chan"}
	};
    qsort(staff,5,sizeof(struct names),comp);
    for(int i=0;i<5;i++)
    printf("%s    %s\n",staff[i].first,staff[i].last);
}
