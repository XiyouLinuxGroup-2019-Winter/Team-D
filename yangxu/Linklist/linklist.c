#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
    int date;
    struct node *next;
} Node;

typedef struct List{
    Node *head;
} List;

void creat(List *p,int n);//链表的创建
void delete_many(List *p,int i);//删除第i个节点
void delete_number(List *p,int n);//删除值为n的所有节点
void change(List *p,int m,int n);//将第m个节点的值改为n
void find_i(List *p,int i);//显示第i个节点的值
void find_k(List *p,int k);//显示值为k的节点顺序
void sort(List *p);

int main ()
{
    List list;
    int n;
    list.head=NULL;
    while(scanf("%d",&n)&&n!=-1){
        creat(&list,n);
    }
    for(Node *q=list.head;q;q=q->next){
        printf("%d ",q->date);
    }
    printf("\n");
    //delete_many(&list,5);
    //delete_number(&list,6);
    //change(&list,1,2);
    //find_i(&list,1);
    //find_k(&list,3);
    //sort(&list);
    for(Node *q=list.head;q;q=q->next){
        printf("%d ",q->date);
    }
    printf("\n");
}

void creat(List *p,int n)
{
    Node *q=(Node *)malloc(sizeof(Node));
    q->date=n;
    q->next=NULL;
    Node *list=p->head;
    if(list){
        while(list->next){
            list=list->next;
        }
       list->next=q;
    } else {
        p->head=q;
    }
}

void delete_many(List *p,int i)
{
    Node *q=p->head;
    Node *l=p->head;
    for(int j=1;l;q=l,l=l->next,j++){
        if(j==i&&i==1){
            p->head=l->next;
            break;
        }else if(j==i){
            q->next=l->next;
            break;
        }
    }
}

void delete_number(List *p,int n)
{
    Node *q=p->head;
    Node *l=q->next;
    while(l!=NULL){
        if(l->date==n){
            q->next=l->next;
            l=q->next;
        }else {
            l=l->next;
            q=q->next;
        }
    }
    if(p->head->date==n){
        p->head=p->head->next;
    }
}

void change(List *p,int m,int n)
{
    Node *l=p->head;
    for(int j=1;l;l=l->next,j++){
        if(j==m){
            l->date=n;
        }
    }
}

void find_i(List *p,int i)
{
    Node *l=p->head;
    for(int j=1;l;l=l->next,j++){
        if(j==i){
           printf("%d\n",l->date);
        }
    }
}

void find_k(List *p,int k)
{
    Node *l=p->head;
    for(int j=1;l;l=l->next,j++){
        if(l->date==k){
            printf("%d\n",j);
        }
    }
}

void sort(List *p)
{
    Node *q;
    Node *l;
    for(q=p->head;q;q=q->next){
        for(l=q->next;l;l=l->next){
            if(q->date>l->date){
                int y=q->date;
                q->date=l->date;
                l->date=y;
            }
        }
    }
}





