#include <iostream>
using namespace std;

class Car {
    int m_age;
    int &m_price = m_age;
public:
    Car(int &price) : m_price(price) {}
};

int main()
{
    return 0;
}

