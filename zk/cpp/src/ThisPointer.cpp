#include <iostream>

using namespace std;

class Human{
public:
    char fishc;

    Human(char fishc);//声明构造函数
};

Human::Human(char fishc) {//定义构造函数
    this->fishc = fishc;
//用this指针来让编译器知道左边的fishc是类的属性
//右边的是构造函数的参数
}

int main()
{


    return 0;
}

