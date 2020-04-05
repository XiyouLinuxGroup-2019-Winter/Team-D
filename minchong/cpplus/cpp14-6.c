#include<stdio.h>
#include<stdlib.h>
struct mame
{
    int num;
    char name[20];
    char ms[20];
    int r;
    int b;
    int l;
};
int main()
{
    struct mame mumb[100]={0};
    FILE *fp;
    int i=0,h;
    char k,g;
    fp=fopen("cbx.bin","ab+");
    if(fp==NULL)
    {
    printf("打开文件失败！");
    exit(EXIT_FAILURE);
    }
    while((fread(&mumb[i],sizeof(struct mame),1,fp))==1)
    i++;
    for(h=0;h<=i;h++)
    printf("%d  %s  %s  %d %d %d \n",mumb[h].num,mumb[h].name,mumb[h].ms,mumb[h].r,mumb[h].b,mumb[h].l);
    fclose(fp);
}
