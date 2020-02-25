#include <iostream>
using namespace std;

class Car {
public:
    const int mc_price;
    Car() : mc_price(0) {}
    void run() const {
        cout << "run()const" << endl;
    }
    void run() {
        cout << "run()" << endl;
    }
};

int main()
{
    Car car;
    car.run();
    const Car car1;
    car1.run();
    return 0;
}

