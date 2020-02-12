#include <iostream>
using namespace std;

class Studnet {
public:
    int m_age;
};

class Worker {
public:
    int m_age;
};

class Undergraduate : public Studnet, public Worker {
public:
    int m_age;
};

int main()
{
    Undergraduate ug;
    ug.m_age = 10;
    ug.Studnet::m_age = 20;
    ug.Worker::m_age = 30;
    cout << ug.Undergraduate::m_age << endl;
    cout << ug.Studnet::m_age << endl;
    cout << ug.Worker::m_age << endl;
    return 0;
}

