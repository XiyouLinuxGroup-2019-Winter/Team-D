#include <iostream>
using namespace std;

class Person {
public:
    int m_age;

    Person() {
        m_age = 0;
        cout << "Person()" << endl;
    }

    Person(int age) {
        m_age = age;
        cout << "Person(int age)" << endl;
    }
};

Person person1(); // 函数声明

Person person1() { // 函数实现
    return Person();
}

Person g_person0; // Person();
Person g_person1(); // 全局的函数声明
// 返回值  函数名
Person g_person2(10); // Person(int)

int main()
{
    Person person0; // Person()
    Person person1(); // 局部的函数声明
    Person person2(20); // Person(int)

    Person *p0 = new Person; // Person()
    Person *p1 = new Person(); // Person()
    Person *p2 = new Person(30); // personn(int)
    return 0;
}

