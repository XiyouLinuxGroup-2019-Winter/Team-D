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

int main()
{
    struct link* p;   
    p = initlink();

    return 0;
}

