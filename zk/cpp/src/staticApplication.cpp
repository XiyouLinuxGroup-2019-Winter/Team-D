#include <iostream>
using namespace std;

class Car {
private:
    static int ms_count;
public:
    Car() {
        ms_count++;
    }
    ~Car() {
        ms_count--;
    }
    static int getCount() {
        return ms_count;
    }
};

int Car::ms_count = 0;

Car g_car;

int main()
{
    Car car;
    Car *p = new Car();
    cout << Car::getCount() << endl;
    cout << car.getCount() << endl;
    return 0;
}

