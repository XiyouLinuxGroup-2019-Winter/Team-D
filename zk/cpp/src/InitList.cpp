#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
    int m_height;

    /*Person(int age, int height) {
        m_age = age;
        m_height = height;
    }*/
    // 语法糖
    Person(int age, int height) : m_age(age), m_height(height) {

    }
    // 这个构造函数与上面的构造函数等价
};

int main()
{
    Person person(18, 180);   
    cout << person.m_age << endl;
    cout << person.m_height << endl;
    return 0;
}

