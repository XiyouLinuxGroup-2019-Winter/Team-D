#include <iostream>

using namespace std;

int quickpow(int a, int n);

int main(int argc, char *argv[]) {
	
	int ans = 1;
	int a, n;
	cin>>a>>n;
	
	while(n)
	{		
		if((n&1) == 1) ans = ans * a % 6662333;
		a = a * a % 6662333;	
		n >>= 1;t
	}

}

int quickpow(int a, int n)
{	
	if(n == 1) return a;
	if(n&1)	return quickpow(a, n>>1) * quickpow(a,  (n>>1) + 1);
	return quickpow(a, n>>1) * quickpow(a, n>>1);
	
}