/*
	两种情况
		一个是走一个周长
		一个是走最短两条路径的两倍
		求min即可
*/
#include <iostream>
#include <algorithm>

using namespace std;

long long mi(long long a , long long b)
{
	return a >= b ? b : a; 	
}

int main()
{
	long long q[3];
	
	for (int i = 0; i < 3 ; i++) {
		cin>>q[i];
	}

	sort(q, q + 3);
	
	printf("%lld", mi(2 * (q[1] + q[0]), q[0] + q[1] + q[2]));
	
}