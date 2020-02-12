#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
};

class Student : virtual public Person {
public:
    int m_score;
};

class Worker : virtual public Person {
public:
    int m_salary;
};

class Undergraduate : public Student ,public Worker {
public:
    int m_grade;
};

int main()
{
    Undergraduate ug;
    ug.m_age = 10;
    return 0;
}

