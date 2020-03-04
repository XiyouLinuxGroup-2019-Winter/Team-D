#include <iostream>
using namespace std;

class Student {
public:
    void eat() {
        cout << "11" << endl;
    }
};

class Worker {
public:
    void eat() {
        cout << "22" << endl;
    }
};

class Undergraduate : public Student, public Worker {
public:
    void eat() {
        cout << "33" << endl;
    }
};

int main()
{
    Undergraduate ug;
    ug.Student::eat();
    ug.Worker::eat();
    ug.Undergraduate::eat();
    ug.eat(); // Undergraduate
    return 0;
}

