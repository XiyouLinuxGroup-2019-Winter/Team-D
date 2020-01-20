#include<stdio.h>
#include<stdlib.h>
struct libi
{
    int data;
    struct libi *next;
    struct libi *froat;
};
typedef struct libi*  libil;
libil creat(void);
libil deletei(libil head,int i);
libil deletek(libil head,int key);
libil sort(libil head);
void  change(libil head,int m,int n);
void  insert(libil head,int a,int b);
int main()
{
    int i,key,ctr,m,n,a,b;
    libil head,p;
    printf("请输入整形数据（输入0结束）：\n");
    head=creat();
    while(1)
    {
    printf("请选择实现功能  1-删除第i个节点   2-删除所有值为k的节点  3-排序  4-修改第i个节点的信息  5-在第i个节点后插入信息  0-退出程序：");
    scanf("%d",&ctr);
    if(ctr==0)
    break;
    switch(ctr)
    {
        case 1:printf("请输入要删除的节点的序号：");
            scanf("%d",&i);
            head=deletei(head,i);
            break;
        case 2:printf("请输入要删除的数据：");
            scanf("%d",&key);
            head=deletek(head,key);
            break;
        case 3:head=sort(head);
               break;
        case 4:printf("请输入要修改的节点序号与修正值：");
               scanf("%d %d",&m,&n);
               change(head,m,n);
               break;
        case 5:printf("请输入要插入的节点序号与插入值：");
               scanf("%d %d",&a,&b);
               insert(head,a,b);
               break;
    }
    for(p=head;p->next!=head;p=p->next)
    printf("%d ",p->data);
    printf("%d\n",p->data);
    }
}
libil creat()
{
    libil head,end,p;
    head=p=end=(libil )malloc(sizeof(struct libi));
    while(1)
    {
        scanf("%d",&p->data);
        if(p->data==0)
        break;
        end->next=p;
        p->froat=end;
        end=p;
        p=(libil )malloc(sizeof(struct libi));
    }
    end->next=head;
    free(p);
    head->froat=end;
    return head;
}
libil deletei(libil head,int i)
{
    libil p;
    p=head;
    int h;
    for(h=1;h<i;h++)
    head=head->next;
    head->froat->next=head->next;
    head->next->froat=head->froat;
    if(i==1)
    p=head->next;
    free(head);
    return p;
}
libil deletek(libil head,int key)
{
    libil p,p1,p2;
    p=(libil)malloc(sizeof(struct libi));
    p->next=head;
    head->froat->next=p;
    head->froat=p;
    p2=p;
    for(p1=head;p1->next!=p;p1=p2->next)
    {
    if(p1->data==key)
    {
        p1->froat->next=p1->next;
        p1->next->froat=p1->froat;
        free(p1);
    }
    else
    p2=p2->next;
    }
    if(p1->data==key)
    {
        p1->froat->next=p->next;
        p->next->froat=p1->froat;
        free(p1);
    }
    else
    {
        p1->next=p->next;
        p->next->froat=p1;
    }
    head=p->next;
    free(p);
    return(head);
}
libil sort(libil head)
{
    int i,h,j;
    libil p1,p2,p4[100];
    for(p1=head,i=0;p1->next!=head;p1=p1->next,i++)
    p4[i]=p1;
    p4[i]=p1;
    for(h=0;h<=i;h++)
    for(j=h;j<=i;j++)
    if(p4[h]->data>p4[j]->data)
    {
        p2=p4[h];
        p4[h]=p4[j];
        p4[j]=p2;
    }
    for(h=1;h<=i;h++)
    {
        p4[h-1]->next=p4[h];
        p4[h]->froat=p4[h-1];
    }
    p4[0]->froat=p4[i];
    p4[i]->next=p4[0];
    return p4[0];
}
void change(libil head,int m,int n)
{
    int i;
    libil p=head;
    for(i=1;i<m;i++)
    p=p->next;
    p->data=n;
}
void insert(libil head,int a,int b)
{
    int i;
    libil p;
    p=(libil)malloc(sizeof(struct libi));
    p->data=b;
    for(i=1;i<a;i++)
    head=head->next;
    p->next=head->next;
    p->froat=head;
    head->next=p;
    p->next->froat=p;
}
