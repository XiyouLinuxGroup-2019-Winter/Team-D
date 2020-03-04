#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
    Person(int age = 0) : m_age(age) {}
    Person(const Person &person) : m_age(person.m_age) {}
};

class Student : public Person {
public:
    int m_score;
    Student(int age = 0, int score = 0) : Person(age), m_score(score) {}
    // 因为Student继承Person所以创建Student对象时, 又有age又有score
    Student(const Student &student) : Person(student), m_score(student.m_score) {}
    // 调用父类的拷贝构造函数
};

int main()
{
    Student stu1(18, 100);
    Student stu2(stu1);
    cout << stu2.m_age << endl;
    cout << stu2.m_score << endl;
    return 0;
}

