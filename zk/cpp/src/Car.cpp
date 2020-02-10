#include <iostream>

#define FULL_GAS 85

using  namespace std;

class Car {
public:
    string color;
    string engine;
    int gas_tank;
    unsigned int wheel;

    void setColor(string clo);
    void setEngine(string eng);
    void setWhell(unsigned int whe);
    void fillTank(int liter);
    int running(void);
    void warning(void);
};
// :: 是作用域解析操作符,作用是告诉编译器这个
// 方法存在何处,或者说是属于哪一个类.

void Car::setColor(string col) {
    color = col;
}

void Car::setEngine(string eng) {
    engine = eng;
}

void Car::setWhell(unsigned int whe) {
    wheel = whe;
}

void Car::fillTank(int liter) {
    gas_tank += liter;
}

int Car::running(void) {
    cout << "我正在以120的时速往前移动...";
    gas_tank--;
    cout << "当前还剩 " << 100 * gas_tank / FULL_GAS << '%' << "油量!\n";

    return gas_tank;
}

void Car::warning(void) {
    cout << "WARNING!!" << "还剩 " << 100 * gas_tank / FULL_GAS << '%' << "油量!";
}
int main()
{
    char i;
    Car mycar, car1;

    mycar.setColor("WHITE");
    mycar.setEngine("V8");
    mycar.setWhell(4);
    
    mycar.gas_tank = FULL_GAS;
    car1 = mycar; 
    // 可以
    while (mycar.running() > 0) {
        if (mycar.running() < 10) {
            mycar.warning();
            cout << "请问是否需要加满油在行驶?\n";
            cin >> i;
            if (i == 'Y' || i == 'y') {
                mycar.fillTank(FULL_GAS);
            }
        }
    }
    return 0;
}

