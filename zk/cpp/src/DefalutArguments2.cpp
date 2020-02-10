#include <iostream>
using namespace std;

int age = 20;

void sum(int v1 = 5, int v2 = age) {
    cout << v1 + v2 << endl; 
}

int main()
{
    sum();
    return 0;
}

