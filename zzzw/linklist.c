#include <stdio.h>
#include "stdlib.h"
#define T int
#define C "%d"

struct list* list_create();
struct list* list_add_fnt(struct list* tail);
struct list* list_add_back(struct list* head);
struct list* list_del_i(int i, struct list *head);
struct list* list_del_key(struct list *head, T key);
void list_search_i(int i, struct list *head);
void list_search_key(T key, struct list *head);
void list_show(struct list *head);
struct list * list_modify(T tar, struct list *head, T new);

struct list{
	 T data;
	struct list* next;
};

int main(int argc, char *argv[]) {
	
}

struct list* list_create()
{
	struct list*p = malloc(sizeof(struct list));
	p->next = NULL;
	
	return p;
}

struct list* list_add_fnt(struct list* tail)
{
	T data;
	struct list *head = tail;
	
	while(1)
	{
		printf("Please enter data (-1 to end):");
		scanf(C, &data);
		
		if(data == -1)  return head;
		
		struct list* temp = malloc(sizeof(struct list));
		temp->next = head;
		temp->data = data;
		head = temp;
	}

}

struct list* list_add_back(struct list* head)
{
	T data;
	
	struct list* cur = head;
	
	while(cur->next != NULL)
		cur = cur->next;
		
	while (1) {
		printf("Please enter data (-1 to end):");
		scanf(C,&data);
		
		if(data == -1) return head;
		
		struct list *p = malloc(sizeof(struct list));
		cur->next = p;
		
		cur->data = data;
		p->next = NULL;
		
		cur = cur->next;
	}
}

struct list* list_del_i(int i, struct list *head)
{
	int cnt = 1;
	struct list *cur = head;
	struct list *prev = NULL;
	
	while(cur->next != NULL && cnt < i)
		prev = cur, cur = cur->next, cnt++;
	
	if(cnt < i) 
		{
			printf("i beyond the boundary");
			return head;
		}
	
	
	prev->next = cur->next;
	free(cur);
	
	return head;
}

struct list* list_del_key(struct list *head, T key)
{
	struct list* cur = head;
	struct list* prev = NULL;	
	
	while(cur->next != NULL)
	{
		if(cur->data == key)
		{
			prev->next = cur->next;
			free(cur);
		}
		
		prev = cur;
		cur = cur->next;
	}

	return head;
}

//
//看具体怎么改
struct list * list_modify(T tar, struct list *head, T new)
{
	struct list *cur = head;
	struct list *prev = NULL;
	
	while(cur->next != NULL && cur->data != tar)
		prev = cur, cur = cur->next;
	
	if(cur->next == NULL)
		{
			printf("Not found target");
			return head;
		}
	
	cur->data = new;
	return head;
}
//

void list_search_i(int i, struct list *head)
{
	int cnt = 1;
	
	struct list *p = head;
	
	while(p->next != NULL && cnt < i)
		p = p->next, cnt++;
	
	if(cnt < i)
		{
			printf("i beyond boundary");
		}
	printf(C,p->data);	
}

void list_search_key(T key, struct list *head)
{
	struct list *cur = head;
	
	while(cur->next != NULL)
	{
		if(cur->data == key)
		{
			printf(C" ", cur->data);
		}
		
		cur = cur->next;
	}
}

void list_show(struct list *head)
{	
	struct list* cur =  head;
	
	while(cur->next != NULL)
	{
		printf(C" ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}