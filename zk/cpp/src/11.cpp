#include <iostream>
using namespace std;

class Car {
    int m_price;
public:
    Car() {}
    Car(int price) : m_price(price) {}
    Car(const Car &car) {}
    void run() {
        cout << "run()" << endl;
    }
};

void test1(Car car) {

}

int main()
{
    Car car1;
    test1(car1);
    return 0;
}

