#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct stu
{
    char word[500];
    struct stu *next;
};
typedef struct stu *  link;
int main()
{
    int q=0,i,k=0,h,ctr,ctr1=0,w=0,l,f,m,n;
    char iss[1000000],mod[500];
    link head,p,p1,p2,p3,num[5001],nu,end;
    head=p=(link)malloc(sizeof(struct stu));
    end=(link)malloc(sizeof(struct stu));
    head->next=end;
    end->next=NULL;
    while((scanf("%c",&iss[q]))!=EOF)
    q++;
    for(i=0;i<q;i++)
    {
    if(iss[i]>='A'&&iss[i]<='Z'||iss[i]>='a'&&iss[i]<='z')
    {
        if(iss[i]>='A'&&iss[i]<='Z')
        iss[i]+=32;
        mod[k]=iss[i];
        k++;
    }
    else
        {
            for(p1=head;p1->next!=NULL;p1=p1->next)
            {
            ctr=strcmp(mod,p1->word);
            if(ctr==0)
            {
                ctr1=1;
                break;
            }
            }
            if(ctr1==0)
                {
                    for(l=0;l<k;l++)
                    p->word[l]=mod[l];
                    p2=(link)malloc(sizeof(struct stu));
                    p->next=p2;
                    p2->next=end;
                    p=p2;
                }
            for(f=0;f<k;f++)
            mod[f]='\0';
            ctr1=0;
            k=0;
        }
    }
    for(p1=head;p1->next!=NULL;p1=p1->next)
    {
        num[w]=p1;
        w++;
    }
    for(i=0;i<w;i++)
    for(q=i+1;q<w;q++)
    if(strcmp(num[i]->word,num[q]->word)>0)
    {
        nu=num[i];
        num[i]=num[q];
        num[q]=nu;
    }
    for(i=0;i<w;i++)
    printf("\n%s",num[i]->word);
    printf("\n");
    return 0;
}
