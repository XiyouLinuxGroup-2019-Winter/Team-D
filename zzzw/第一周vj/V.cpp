//排序题
#include <iostream>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
	int a[10050];
	
	int n;
	cin>>n;
	
	for(int i = 0; i < n; i++)
		cin>>a[i];
	
	sort(a, a + n);
	
	cout<<a[n / 2];	
}