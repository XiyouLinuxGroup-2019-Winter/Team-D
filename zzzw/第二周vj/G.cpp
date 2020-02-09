#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <set>
using namespace std;
set <string> ans;

int main(int argc, char *argv[]) {
	string in, out;
	
	while(cin>>in)
	{
		for (int i = 0; i < in.length(); i++) {
			if (isalpha(in[i])) {
				in[i] = tolower(in[i]);
			}
			else in[i] = ' ';
		}
		
		stringstream ss(in);
		
		while(ss>>out)
			ans.insert(out);		
	}
	
	for (auto i = ans.begin(); i != ans.end(); i++) {
		cout<<*i<<" "<<endl;
	}
}