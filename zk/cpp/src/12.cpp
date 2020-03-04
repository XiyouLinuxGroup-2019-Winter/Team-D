#include <iostream>
using namespace std;

class Car {
public:

};

Car test2() {
    Car car;   
    return car;
}

int main()
{
    Car car2 = test2();
    // 编译器会做优化, 使test2函数里面拷贝构造
    // 出来的对象就直接是car2了, 不会再调用
    // 一次拷贝构造
    return 0;
}

