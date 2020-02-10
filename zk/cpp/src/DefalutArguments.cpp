#include <iostream>
using namespace std;

int func(int v1, int v2 = 3, int v3 = 5) {
    return v1 + v2 + v3; 
}

int func1(int v1 = 3, int v2 = 3, int v3 = 4) {
    return v1 + v2 + v3; 
}

/*
int func2(int v1 = 3, int v2) {

} 
错误,默认参数必须从右到左*/

int main()
{
    cout << func(1) << endl;
    cout << func(1,2) << endl;
    cout << func(1, 2, 3) << endl;
    cout << func1() << endl;
    return 0;
}

