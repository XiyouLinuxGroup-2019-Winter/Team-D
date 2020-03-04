#include <iostream>
using namespace std;

class Person {
private:
    int m_age;

public:
    Person(int age) : m_age(age){  }
    int getAge() {
        return m_age;
    }
};

class Student : public Person {
private:
    int m_no;

public:
    // 不能访问m_age, 所以只能调用构造函数
    Student(int age, int no) : Person(age), m_no(no) {  }
    int getNo() {
        return m_no;
    }
};

int main()
{
    Student student(10, 20);
    cout << student.getAge() << '\n' <<
        student.getNo() << endl;
    return 0;
}

