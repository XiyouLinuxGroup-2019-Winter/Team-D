#include <iostream>
#include <cstdio>
#include "algorithm"
using namespace std;
int n,A[100000],B[100000],C[100000],D[100000],c[100000000],d[100000000];
int t = 0,s = 0, w;
void search(int k)
{
		int *g = lower_bound(c,c+s,k);
		int *h = upper_bound(c,c+s,k);
		int q = h-g;
		t += q;
}
int main()
{   
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>A[i];
		cin>>B[i];
		cin>>C[i];
		cin>>D[i];

	}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			c[s] = A[i] + B[j];
			d[s] = C[i] + D[j];
			s++;
		}
	}
	sort(c,c+s);
	sort(d,d+s);
	for(int i = 0;i < s;i++)
	{
		w =-d[i];
		search(w);
	}
	cout<<t;

} 