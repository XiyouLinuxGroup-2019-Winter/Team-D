#include <iostream>

using namespace std;

class Student {
private:
    char *m_name;
    int m_age;
    float m_score;

public:
    void setname(char *name);
    void setage(int age);
    void setscore(float score);
    void show();
};
//成员函数的定义
void Student::setname(char *name) {
    m_name = name;
}

//在类的内部(定义类的代码内部),无论成员被声明为public,protected还是private都是可以互相访问的,没有访问权限的限制.
//在类的外部(定义类的代码之外),只能通过对象访问成员,并且通过对象只能访问public属性的成员,不能访问private protected属性的成员.
//类的声明和成员函数的定义都是类定义的一部分.
//类中的成员变量 m_name、m_age 和m_ score 被设置成 private 属性，在类的外部不能通过对象访问。也就是说，私有成员变量和成员函数只能在类内部使用，在类外都是无效的。
//成员函数 setname()、setage() 和 setscore() 被设置为 public 属性，是公有的，可以通过对象访问.
//成员变量大都以m_开头,这是约定俗成的写法,以m_开头既可以一眼看出这是成员变量,又可以和成员函数中的形参名字区分开.
//因为三个成员变量都是私有的,不能通过对象直接访问,所以必须借助三个public属性的成员函数来修改他们的值.下面的代码是错误的:
//Student stu;
//m_name m_age m_score 是私有成员变量,不能在类外部通过对象访问和修改
//stu.m_name = "小明";
//stu.m_age = 15;
//stu.m_score = 92.5f;
//stu.show();

void Student::setage(int age) {
    m_age = age;
}

void Student::setscore(float score) {
    m_score = score;
}

void Student::show() {
    cout << m_name << "的年龄是" << m_age << ", 成绩是"<< m_score << endl;
}

int main()
{
    //在栈上创建对象
    Student stu;
    stu.setname("小明");
    stu.setage(15);
    stu.setscore(92.5f);
    stu.show();

    //在堆上创建对象
    Student *pstu = new Student;
    pstu->setname("李华");
    pstu->setage(16);
    pstu->setscore(96);
    pstu->show();

    return 0;
}

