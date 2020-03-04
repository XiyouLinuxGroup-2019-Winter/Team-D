#include <iostream>
using namespace std;

void display(int a, int b = 20) {
    cout << a << endl;
}

void display(int a) {
    cout << a << endl;
}

int main()
{
    display(10);
    // 10既可以传给第一个也可以传给第二个, 产生二义性
    return 0;
}

