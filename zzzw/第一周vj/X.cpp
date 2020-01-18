#include <iostream>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
	long long  a[100050];
	
	int n;
	cin>>n;
	
	for (int i = 0; i < n; i++) 
		cin>>a[i];		
	
	sort(a,a + n);
	
	int i = 0;
	while(i < n && a[i] == a[0])
		i++;

	if(i == n - 1) printf("0");
	else 
		{
			int j = n - 1;
			while(j >= i && a[j] == a[n - 1])
					j--;
			if(j == i - 1)
				printf("0");		
			else {
				printf("%d", j - i + 1);
			}
		}
}