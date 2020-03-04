#include <iostream>
using namespace std;

int sum(const int &v1,const int &v2) {
    return v1 + v2;
}


int main()
{
    // 非const实参
    int a = 10;
    int b = 20;
    sum(a, b);
    
    // const实参
    const int c = 10;
    const int d = 20;
    sum(c, d);

    sum(10, 20);
    return 0;
}

