#include <iostream>
using namespace std;

class Student {
private:
    int m_score;
public:
    Student(int score) : m_score(score) {}
};

class Worker {
private:
    int m_salary;
public:
    Worker(int salary) : m_salary(salary) {}
};

class Undergraduate : public Student, public Worker {
private:
    int m_grade;
public:
    Undergraduate(int score, int salary, int grade)
        : Student(score), Worker(salary), m_grade(grade) {}
    // 调用父类的构造函数
};

int main()
{
    Undergraduate graduate(100, 2000, 3);
    return 0;
}

