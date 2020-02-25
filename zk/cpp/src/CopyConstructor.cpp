#include <iostream>
using namespace std;

class Car {
    int m_price;
    int m_length;
public:
    Car(int price = 0, int length = 0) : m_price(price), m_length(length) {
        cout << "Car(int price = 0, int length = 0)" << endl;
    }
    // 拷贝构造函数
    Car(const Car &car) {
        cout << "Car(const Car &car)" << endl;
        m_price = car.m_price;
        m_length = car.m_length;
    }

    void display() {
        cout << "price =" << m_price << ", length = " << m_length << endl;
    }
};

int main()
{
    Car car1;
    Car car2(100);
    Car car3(100, 5);
    // 利用已经存在的car3对象创建了一个car4新对象
    // car4初始化时会调用拷贝构造函数
    Car car4(car3);
    car4.display();
    return 0;
}

