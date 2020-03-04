#include <iostream>
using namespace std;

int main()
{
    int age = 10;

    // 定义了一个age的引用
    int &refAge = age;
    refAge = 20;
    
    cout << age << endl;
    // 结果是20
    return 0;
}

