#include <iostream>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
	long long  a[10050];
	int n;
	
	cin>>n;
	
	for (int i = 0; i < n; i++) 
		cin>>a[i];
	
	sort(a, a + n);
	
	if(n % 2 == 0)
		cout<<a[n / 2 - 1];
	else cout<<a[n / 2];
}