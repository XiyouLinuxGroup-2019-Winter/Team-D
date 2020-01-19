#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//头节点为空
struct list{
	int data;
	struct list *prev;
	struct list *next;	
	int cnt;
};

struct list* list_crete();
struct list* list_push_back(struct list *head);
struct list *list_push_fnt(struct list *head);
struct list* list_del_i(struct list *head, int i);
struct list* list_del_key(struct list *head, int key);
struct list *list_modify(struct list *head, int key, int change);
struct list* list_search_i(struct list *head, int i);
struct list *list_search_key(struct list *head, int key);
void list_show(struct list* head);

int main(int argc, char *argv[]) {
	struct list *head;
	
	head = list_crete();
	
	head = list_push_back(head);
	
	list_show(head);
	
//	head = list_modify(head, 3, 5);
	
	list_search_key(head, 3);
//	list_show(head);
}


struct list* list_crete()
{
	struct list *p = malloc(sizeof(struct list));
	p->next = NULL;
	p->prev = NULL;
	p->cnt = 0;
	
	return p;
}

struct list* list_push_back(struct list *head)
{	
	struct list *cur = head;
		
	while(cur->next != NULL)
		cur = cur->next;
		
	while(1)
	{
		printf("Please enter dat(-1 to end) :");
		int s;
		
		scanf("%d", &s);
		if(s == -1 ) return head;
		
		struct list* p = malloc(sizeof(struct list));
		p->data = s;
		p->next = NULL;
		p->prev = cur;
		
		cur->next = p;
		cur = cur->next;
		
		head->cnt++;
	}
}

struct list *list_push_fnt(struct list *head)
{
	
	while(1)
	{
		printf("Please enter dat(-1 to end) :");
		int s;
		
		scanf("%d", &s);
		if(s == -1 ) return head;
		
		struct list *p = malloc(sizeof(struct list));
		p->data = s;
		p->next = head->next;
		p->prev = head;
		
		head->cnt++;
		head->next = p;
		head->cnt++;
//		head->data = s;
//		head->prev = p;
//		
//		p->prev = NULL;
//		p->next = head;
//		
//		head = p;
	}	
		
}

void list_show(struct list* head)
{	
	struct list* cur = head;
	
	while(cur->prev == NULL)
		cur = cur->next;
		
	while(cur->next != NULL)
	{	
		printf("%d ", cur->data);
		cur = cur->next;
	}
	
	printf("%d\n", cur->data);
}

struct list* list_del_i(struct list *head, int i)
{
	if(head->cnt < i)
		{
			printf("i beyond the boundary!\n");
			return head;
		}
	
	struct list *cur = head;
	
	cur = cur->next;
	int t = 1;
	while(t != i)
		cur = cur->next, t++;
	
	if(cur->next == NULL)
		{
			cur->prev->next = NULL;	
			free(cur);	
		}
	else {	
		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
	
		free(cur);
	}
	return head;
}

struct list* list_del_key(struct list *head, int key)
{
	struct list *cur = head;
	
	while(cur->next != NULL)
	{
		if(cur->data == key)
		{
			
			struct list *temp = cur->next;
			
			cur->next->prev =  cur->prev->next;
			cur->prev->next = cur->next;
			
			free(cur);	
			cur = temp;
		}
		
		else cur = cur->next;	
	}
	
	if(cur->data == key)
	{
		cur->prev->next = NULL;
		free(cur);
	}
	
	return head;
}


struct list *list_modify(struct list *head, int key, int change)
{
	struct list *cur = head;
	
	while(cur->next != NULL && cur->data != key)
		cur = cur->next;
	
	if(cur->next != NULL)
		cur->data = change;
	else if(cur->data == key){
		cur->data =change;
	}
	else {		
		printf("Not Find");
	}
	return head;

}

struct list* list_search_i(struct list *head, int i)
{
	if(head->cnt < i)
	{
		printf("i beyond boundary ");
		return head;
	}
	
	struct list *cur = head;
	
	int cnt = 0;
	while(cnt != i)
		cur = cur->next, cnt++;
	
	printf("i's(i == %d) data is %d", i, cur->data);
	return cur->prev->next;
}

struct list *list_search_key(struct list *head, int key)
{
	struct list *cur = head;
	
	while(cur->next != NULL && cur->data != key)
		cur = cur->next;
	
	if(cur->data == key)
		return cur;
	else {
		printf("Not Find");
		return head;
	}
}