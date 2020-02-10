#include <iostream>
using namespace std;

class Person {
public:
    int m_age;
    int m_height;

    Person(int age = 0, int height = 0);
};

Person::Person(int age, int height) : m_age(age), m_height(height) {
    
}

int main()
{
    Person person;
    return 0;
}

