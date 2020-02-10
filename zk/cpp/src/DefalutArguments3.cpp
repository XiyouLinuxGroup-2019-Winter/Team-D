#include <iostream>
using namespace std;

void func(int v1, void(*p)(int)) {
    p(v1);
}

void test(int a) {
    cout << a << endl;
}

int main()
{
    func(20, test);

    return 0;
}

