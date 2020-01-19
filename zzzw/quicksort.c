#include <stdio.h>
#include <stdlib.h>

//void quicksort(int *a, int *temp, int l, int r);
void quicksort(int *a, int l, int r);

int main(int argc, char *argv[]) {
	int a[] = {4, 2, 3, 1 , 5, 7, 9, 8};
	
	quicksort(a, 0, 7);
	
	for (int i = 0; i < 8; i++) {
		printf("%d ", a[i]);
	}	
}

//需要开另一个数组,会有空间开销
//void quicksort(int *a, int *temp, int l, int r)
//{
//	if(l >= r) return ;
//	
//	int part_element = a[rand()%(r - l + 1) + l];		//注意这个rand的写法
//	int lc = l;
//	int rc = r;
//	
//	for(int i = l; i <= r; i++)
//	{
//		if(a[i] < part_element)	temp[lc++] = a[i];
//		else if(a[i] > part_element) temp[rc--] = a[i];
//	}
//	
//	for(int i = l; i < lc; i++)
//		a[i] = temp[i];
//	for(int i = lc; i <= rc; i++) 
//		a[i] = part_element;
//	for(int i = rc + 1; i <= r; i++)
//		a[i] = temp[i];
//	
//	quicksort(a, temp, l, lc - 1);
//	quicksort(a, temp, rc + 1, r);
//	
//}


void quicksort(int *a, int l, int r)
{
	if(l >= r) return ;

	int mid = rand() % (r - l + 1) + l;
	int part_element = a[mid];
	int lc = l;
	int rc = r;
	
	for(int i = l; lc < rc; i++)
	{
		if(a[i] < part_element)
			{
				int c = a[lc];
				a[lc] = a[i];
				a[i] = c;
				lc++;
			}
		else if(a[i] > part_element)
			{
				int c = a[rc];
				a[rc] = a[i];
				a[i] = c;
				rc--;
				i--;
			}	
	}
	
	a[lc] = part_element;
	
	quicksort(a, l, lc - 1);
	quicksort(a, rc + 1, r);
}

