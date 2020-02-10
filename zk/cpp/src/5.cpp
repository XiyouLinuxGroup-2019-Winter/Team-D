#include <iostream>
using namespace std;

class Person {
public:
    int m_age;

    Person(int age) {
        cout << "Person::Person(int age)" << endl;
    }
};

class Student : public Person {
public:
    int m_no;

    Student() : Person(10) {
        cout << "Student::Student()" << endl;
    }
    //父类缺少无参的构造函数, 子类的构造函数
    //必须显式的调用父类的有参构造函数.
};

int main()
{
    Student student;
    return 0;
}

