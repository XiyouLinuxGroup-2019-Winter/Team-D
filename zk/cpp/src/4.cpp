#include <iostream>
using namespace std;

class Person {
public:
    int m_age;

    Person() {
        cout << "Person::Person()" << endl;
    }

    Person(int age) {
        cout << "Person::Person(int age)" << endl;
    }
};

class Student : public Person {
public:
    int m_no;
    
    Student() : Person(10) {
        cout << "Student::Student()" << endl;
    }
};

int main()
{
    Student student;

    return 0;
}

