#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
    int m_height;

    Person() : Person(0, 0) {}
    Person(int age, int height) : m_age(age), m_height(height) {}
};

int main()
{
    Person person; 
    return 0;
}

