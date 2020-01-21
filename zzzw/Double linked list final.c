#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define	T	int 
#define inp(X) scanf("%d", &X)
#define oup(X) printf("%d ", X)
#define flag  -1	
#define flagcmp(X)	if(X == flag) return head

struct list{
	T data;
	int cnt;
	struct list *prev;
	struct list *next;
	
};

struct list * list_create();
struct list* list_push_back(struct list *head);
struct list* list_push_fnt(struct list *head);
struct list* list_del_i(int i, struct list *head);
struct list *list_del_key(T key, struct list* head);
void list_search_key(struct list *head, T key);
struct list * list_search_i(struct list *head, T tar);
struct list* list_modify(struct list* head, T key);
void *list_quicksort(struct list *head);
void list_show(struct list *head);

int main(int argc, char *argv[]) {
	struct list *head = list_create();
	head = list_push_back(head);
	list_show(head);
	list_quicksort(head);
	list_show(head);
			
}

struct list * list_create()
{
	struct list *p = malloc(sizeof(struct list));
	struct list *tail =  malloc(sizeof(struct list));
	
	p->prev = tail;
	p->next = tail;
	p->cnt = 0; 
	
	tail->next = p;
	tail->prev = p;
	tail->cnt = 0;
	
	return p;
}

struct list* list_push_back(struct list *head)
{
	struct list* tail = head->prev;
	
	while(1)
	{
		printf("Please enter data (-1 to end):");
		T t;
		inp(t);
		
		flagcmp(t);
				
		struct list *p = malloc(sizeof(struct list));
		p->data = t;
		p->next = tail;
		p->prev = tail->prev;
//		p->cnt = ++(head->cnt);	暂且先不计数 会和push_fnt弄乱
			
		tail->prev->next = p;
		tail->prev = p;
		tail->cnt++;
		
		head->cnt++;
		head->prev->cnt = head->cnt;
	}
	
}


struct list* list_push_fnt(struct list *head)
{
	struct list *cur = head->next;
	
	while (1) {
		printf("Please enter data(-1 to end):");
		T s;
		inp(s);
		
		flagcmp(s);
		
		struct list *p = malloc(sizeof(struct list));
		p->data = s;
		p->prev = head;
		p->next = head->next;
									///这里技术push back和fnt会弄乱 
		head->next = p;
		head->cnt++;
	}		
}

void list_show(struct list *head)
{
	struct list* cur = head->next;
	
	while(cur->next != head->prev)
		oup(cur->data), cur = cur->next;
	oup(cur->data);
	puts("");
}



struct list* list_del_i(int i, struct list *head)
{
	if(head->cnt < i)
		{
			printf("i beyond the boundary!\n");
			return head;
		}
		
	int cnt = 0;
	struct list *cur = head;
	
	while(cnt < i)
		cur = cur->next, cnt++;
	
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	
	free(cur);
	
	return head;
}

struct list *list_del_key(T key, struct list* head)
{
	struct list* cur = head;
	
	while(cur->next !=  head)
		{
			
			if(cur->data == key)
				{
					cur->prev->next = cur->next;
					cur->next->prev = cur->prev;
					
					free(cur);
				}
			
			cur = cur->next;
		}
		
	return head;
}

struct list * list_search_i(struct list *head, T tar)
{
	struct list *cur = head;
	while(cur->next != head && cur->data != tar)
		cur = cur->next;	
	if(cur->data == tar)
		return cur;
	printf("Not Found!\n");
	return head;
}

//不太懂这个找到所有key 要怎么处理
void list_search_key(struct list *head, T key)
{
	struct list *cur =  head;
	int cnt = 1;
	printf("key value has ");
	bool vis = false;
	
	while(cur->next != head)
	{	
		if(cur->data == key)			
			printf("%d ", cnt), vis = 1;
		
		cur = cur->next;
		cnt++;
	}
	
	if(vis == true)	printf("not found!\n");
}

struct list* list_modify(struct list* head, T key)
{
	struct list *cur = list_search_i(head, key);
	if(cur == head)
	{
		printf("Not Found!\n");
		return head;
	}
	
	cur->data = key;
	return head;
}


void mergesort(struct list *l, struct list *r, int n)
{		
	if(l == r) return ;
	struct list *mid = l;
	for(int i = 0; i < n; i++)
		mid = mid->next;
	
	mergesort(l, mid, n / 2);
	mergesort(mid->next, r, n / 2);
	
	struct list *rc = r;
	struct list *lc = l;
	
	struct list *new = NULL;
	
	while(rc != mid && lc != mid)
	{
		if(lc->data <= rc->data)		
			{
				
				
			}
		
	}
	
	return ;
}

void list_sort(struct list *head)
{
	mergesort(head->next->next, head->prev->prev, head->cnt / 2);
	
}

//struct list *quicksort(struct list *head)
//{
//	struct list *
//	
//	
//}

