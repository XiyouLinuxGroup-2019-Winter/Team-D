#include <iostream>
using namespace std;

class JobBaomu {
public:
    virtual void clean() = 0;
    virtual void cook() = 0;
    // 因为没有具体实现, 用来定义规范, 所以定义为
    // 纯虚函数
};

class JobTeacher {
public:
    virtual void playFootball() = 0;
    virtual void playBaseball() = 0;
};

class Student : public JobBaomu, public JobTeacher {
public:
    int m_score;
    void clean() {

    }
    void cook() {

    }
    void playFootball() {

    }
    void playBaseball() {

    }
};

class Worker : public JobTeacher {
    int m_salary;
public:
    void playFootball() {

    }
    void playBaseball() {

    }
};

int main()
{
    JobBaomu *stu = new Student();
    stu->clean();
    stu->cook();
    return 0;
}

