#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
};

class Student : public Person {
public:
    int m_score;
};

int main()
{
    Person *p = new Student();
    p->m_age = 10;
    // 安全
    /*
    Student *p = (Student*) new Person();
    p->m_age = 10;
    p->m_score = 10;;
    不安全
    */
    return 0;
}

