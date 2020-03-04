#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
    int m_height;
    Person(int age = 0, int height = 0) : m_age(age), m_height(height) {

    }
    // 一个构造函数相当于写了3个构造函数
};

int main()
{
    Person person1;
    Person person2(19);
    Person person3(20, 180);
    return 0;
}

