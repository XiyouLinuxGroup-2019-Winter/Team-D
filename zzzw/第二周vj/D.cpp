#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

priority_queue <long long ,vector<long long >,greater<long long> > q2;
priority_queue <long long ,vector<long long >,greater<long long> > q3;
priority_queue <long long ,vector<long long >,greater<long long> > q5;
priority_queue <long long> ans;

int main(int argc, char *argv[]) {
	ans.push(1);
	q2.push(ans.top() * 2);
	q3.push(ans.top() * 3);
	q5.push(ans.top() * 5);
	
	while(1)
	{	
		long long t = min(min(q2.top(), q3.top()), q5.top());
		if(q2.top() == t)	q2.pop();
		if(q3.top() == t)	q3.pop();
		if(q5.top() == t)	q5.pop();
		
		ans.push(t);
		q2.push(t * 2);
		q3.push(t * 3);
		q5.push(t * 5);
		
		if(ans.size() == 1500)
		{
			printf("The 1500'th ugly number is %lld.\n", ans.top());
			break;
		}
	}
}