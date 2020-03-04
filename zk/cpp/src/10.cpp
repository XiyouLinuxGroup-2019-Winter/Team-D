#include <iostream>
using namespace std;

class Student {
public:
    virtual void study() {
        cout << "123" << endl;
    }
};

class Worker {
public:
    virtual void work() {
        cout << "456" << endl;
    }
};

class Undergraduate : public Student, public Worker {
public:
    void study() {
        cout << "111" << endl;
    }
    void work() {
        cout << "333" << endl;
    }
    void play() {
        cout << "222" << endl;
    }
};

int main()
{
    Student *p = new Undergraduate();

    p->study();

    return 0;
}

