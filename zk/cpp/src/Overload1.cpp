#include <iostream>
using namespace std;

void display(int a) {
    cout << "int" << a << endl;
}

void display(long a) {
    cout << "long" << a << endl;
}

void display(double a) {
    cout << "double" << a << endl;
}

int main()
{
    display(10);// int类型
    display(10L);// long类型
    display(10.0);// double类型
    return 0;
}

