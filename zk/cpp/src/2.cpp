#include <iostream>
using namespace std;

class Person {
public:
    int m_id;
    int m_age;
    int m_height;
    void display() {
        cout << m_id << m_age << m_height << endl;
    }
};

int main()
{
    Person person;
    person.m_id = 1;
    person.m_age = 2;
    person.m_height = 3;
    cout << &person << endl;
    cout << &person.m_id << endl;
    cout << &person.m_age << endl;
    cout << &person.m_height << endl;

    return 0;
}

