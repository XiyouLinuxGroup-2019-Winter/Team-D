#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
}Node;

typedef Node* LinkList;

LinkList p;

void initLinkList();
int addHeadLinkList();
int addTailLinkList();
int delLinkListI(int i);
int delLinkListKey(int key);
int modifyLinkList(int oldData);
LinkList searchLinkListByI(int i);
LinkList searchLinkListByKey(int key);
void displayLinkList();


int main()
{

    return 0;
}

void initLinkList() {
    LinkList p = (LinkList)malloc(sizeof(Node));
    p->next = NULL;
}

int addHeadLinkList() {
    LinkList s = (LinkList)malloc(sizeof(Node));
    if (s == NULL) {
        printf("内存分配失败\n");
        return 0;
    }
    printf("please input new data: ");
    scanf("%d", &s->data);
    s->next = p->next;
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
    printf("please input new data: ");
    scanf("%d", &s->data);
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = s;
    s->next = NULL;
    return 1;
}

int delLinkListI(int i) {
    int j = 1;
    LinkList cur = p;
    while (cur->next != NULL) {
        cur = cur->next;
        j++;
        if (j == i) {
            break;
        }
    }
    if (cur->next == NULL) {
        printf("没有该位置结点\n");
        return 0;
    }
    LinkList tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return 1;
}

int delLinkListKey(int key) {
    LinkList cur = p;
    while (cur->next != NULL) {
        if (cur->next->data == key) {
            break;
        }
        cur = cur->next;
    }
    if (cur->next == NULL) {
        printf("没有该位置结点\n");
        return 0;
    }
    LinkList tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return 1;
}

int modifyLinkList(int oldData) {
    LinkList cur = p;
    while (cur->next != NULL) {
        cur = cur->next;
        if (cur->data == oldData) {
            break;
        }
    }
    if (cur->next == NULL) {
        printf("没有该结点\n");
        return 0;
    }
    printf("请输入新数据\n");
    scanf("%d", &cur->data);
    return 1;
}

LinkList searchLinkListI(int i) {
    LinkList cur = p;
    int j = 0;
    while (cur->next != NULL) {
        cur = cur->next;
        j++;
        if (j == i) {
            break;
        }
    }
    if (cur->next == NULL) {
        printf("没有该位置结点\n");
        return 0;
    }
    return cur;
}

LinkList searchLinkListKey(int key) {
    LinkList cur = p;
    while (cur->next != NULL) {
        cur = cur->next;
        if (cur->data == key) {
            break;
        }
    }
    if (cur->next == NULL) {
        printf("没有该结点\n");
        return 0;
    }
    return cur;
}

void displayLinkList() {
    LinkList cur = p;
    while (cur->next != NULL) {
        cur = cur->next;
        printf("%d\t", cur->data);
    }
}



