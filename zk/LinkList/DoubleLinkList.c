#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
}Node;

typedef Node* LinkList;

LinkList p;

void initLinkList();
int addHeadLinkList();
int addTailLinkList();
int delLinkListByI(int i);
int delLinkListByKey(int key);
int modifyLinkList(int oldData);
LinkList searchLinkListByI(int i);
LinkList searchLinkListByKey(int key);
void displayLinkList();

int main()
{
    return 0;
}

void initLinkList() {
    p = (LinkList)malloc(sizeof(Node));
    p->next = p;
    p->prev = p;
}

int addHeadLinkList() {
    LinkList s = (LinkList)malloc(sizeof(Node));
    if (s == NULL) {
        printf("内存分配失败\n");
        return 0;
    }
    printf("请输入数据\n");
    scanf("%d", &s->data);
    s->prev = p;
    s->next = p->next;
    p->next->prev = s;
    p->next = s;
    return 1;
}

int addTailLinkList() {
    LinkList s = (LinkList)malloc(sizeof(Node));
    if (s == NULL) {
        printf("内存分配失败\n");
        return 0;
    }
    LinkList cur = p;
    while (1) {
        cur = cur->next;
        if (cur->next == p) {
            break;
        }
    }
    s->prev = cur;
    s->next = cur->next;
    cur->next->prev = s;
    cur->next = s;
    return 1; 
}

int delLinkListByI(int i) {
    LinkList cur = p;
    int j = 1;
    while (j != i || cur->next != p) {
        cur = cur->next;
        j++;
        if (j == i || cur->next == p) {
            break;
        }
    }
    if (cur->next == p) { // 注意, 只要cur->next是p了, 就返回
        return 0;         // 因为cur是要删除的结点的前结点
    }
    LinkList tmp = cur->next;
    cur->next = tmp->next;
    tmp->next->prev = cur;
    free(tmp);
    return 1;
}

int delLinkListByKey(int key) {
    LinkList cur = p;
    while (cur->next->data != key || cur->next->next != p) {
        cur = cur->next;
    }
    if (cur->next->data != key) {
        return 0;
    }
    LinkList tmp = cur->next;
    cur->next = tmp->next;
    tmp->next->prev = cur;
    free(tmp);
    return 1;
}

int modifyLinkList(int oldData) {
    LinkList cur = p;
    while (cur->data != oldData || cur->next != p) {
        cur = cur->next;
    }
    if (cur->data != oldData) {
        return 0;
    }
    printf("请输入新数据\n");
    scanf("%d", &cur->data);
    return 1;
}

LinkList searchLinkListByI(int i) {
    LinkList cur = p;
    int j = 0;
    while (1) {
        cur = cur->next;
        if (j == i || cur->next == p) {
            break;
        }
    }
    if (j != i) {
        return 0;
    }    
    return cur; 
}

LinkList searchLinkListByKey(int key) {
    LinkList cur = p;
    while (1) {
        cur = cur->next;
        if (cur->data == key || cur->next == p) {
            break;
        }
    }
    if (cur->data != key) {
        return 0;
    }
    return cur;
}

void displayLinkList() {
    LinkList cur = p;
    while (1) {

    }
}






