#include <iostream>
using  namespace std;

void test(int a) {
    cout << a << endl;
}

void func(int v1, void(*p)(int) = test) { // 默认参数是函数名
    p(v1);
}

int main()
{
    func(20);
    return 0;
}

