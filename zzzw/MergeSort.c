#include <stdio.h>

void mergesort(int *a, int *temp, int l, int r);

int main()
{
	
}

void mergesort(int *a, int *temp, int l, int r)
{
	if(l == r) return ;
	
	int mid = (l + r) / 2;
	mergesort(a, temp, l, mid);
	mergesort(a, temp, mid + 1, r);
	
	int lc = l;
	int rc = mid + 1;
	int i = l;
	
	while(lc <= mid && rc <= r)
	{
		if(a[lc] >= a[rc])
			temp[i++] = a[rc++];
		else temp[i++] = a[lc++];
	}
	
	while(rc <= r)
		temp[i++] = a[rc++];
	while(lc <= mid)
		temp[i++] = a[lc++];
		
	for(int j = l; j <= r; j++)
		a[j] = temp[j];
	
	return ;
}