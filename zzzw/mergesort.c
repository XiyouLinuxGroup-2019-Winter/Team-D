#include <stdio.h>

void MergeSort(int l, int r);

int a[] = {0, 5, 4, 3, 2 ,1};
int ans[1000];

int main(int argc, char *argv[]) {
	
	
	MergeSort(1, 6);
	
	for(int i = 1; i <= 6; i++)
		printf("%d ", ans[i])	;
}

void MergeSort(int l, int r)
{
	if(l == r) return ;
	
	int mid = (r + l) / 2;
	
	MergeSort(l, mid);
	MergeSort(mid + 1, r);
	
	int lc = l;
	int rc = mid + 1;
	int i = l;
	
	while(lc <= mid && rc <= r)
	{
		if(a[lc] < a[rc])	ans[i++] = a[lc++];
		else 				ans[i++] = a[rc++];
	}
	
	while(lc <= mid)
		for(int j = lc; j <= mid; j++)
			ans[i++] = a[lc++];
	
	while(rc <= mid)
			for(int j = rc; j <= mid; j++)
				ans[i++] = a[rc++];		
	for (int j = l; j <= r; j++) {
		a[j] = ans[j];
	}			
	return ;
}