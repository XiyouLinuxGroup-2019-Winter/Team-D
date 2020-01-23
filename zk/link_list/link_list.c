#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct link {
    char name[10];
    struct link *pnext;
};
struct link* initlink() {
    struct link *head, *current, *next;
    head = (struct link*)malloc(sizeof(struct link));
    printf("please input name\n");
    scanf("%s", head->name);
    current = head;
    char x;
    printf("continue or eixt:(y/n)\n");
    scanf("%c", &x);
    while (x == 'y') {
        printf("please input name\n");
        next = (struct link*)malloc(sizeof(struct link));
        scanf("%s", next->name);
        current->pnext = next;
        current = next;
        printf("continue or eixt:(y/n)\n");
        scanf("%c", &x);
    }
    current->pnext = NULL;
    return head;
}

void display(struct link *p) {
    while (p->pnext != NULL) {
        printf("%s\n", p->name);
        p = p->pnext;
    }
    printf("%s\n", p->name);
}

void top_insert(struct link *p) {
    int position;
    printf("please input insert position:\n");
    scanf("%d", &position);
    struct link *current, *insert;
    insert = (struct link*)malloc(sizeof(struct link));
    printf("please input insert name:\n");
    scanf("%s", insert->name);
    current = p;
    int cnt = 1;
    while (cnt != position) {
        current = current->pnext;
        cnt++;
    }
    insert->pnext = current->pnext;
    current->pnext = insert;
}

void dellink(struct link *p) {
    printf("please input del position:\n");
    int position;
    struct link *current;
    scanf("%d", &position);
    int cnt = 1;
    current = p;
    while (cnt != position) {
        current = current->pnext;
        cnt++;
    }
    current->pnext = current->pnext->pnext;
}

int main()
{
    struct link* p;   
    p = initlink();
    display(p);    
    top_insert(p);
    display(p);
    dellink(p);
    display(p);
    return 0;
}

