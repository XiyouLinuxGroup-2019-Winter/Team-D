#include <iostream>
#include <cstring>
using namespace std;

class Car {
private:
    int m_price;
    char *m_name;
    void copyName(const char *name) {
        if (name == NULL) return;
        // 申请新的堆空间
        m_name = new char [strlen(name) + 1] {};
        // 拷贝字符串数据到新的堆空间
        strcpy(m_name, name);
    }
public:
    Car(int price = 0, const char *name = NULL) : m_price(price) {
        copyName(name);
    }
    Car(const Car &car) : m_price(car.m_price) {
        copyName(car.m_name);
    }
    ~Car() {
        if (m_name != NULL) {
            delete[] m_name;
            m_name = NULL;
        }
    }
    void display() {
        cout << "price is" << m_price << ", name is" << m_name << endl;
    }
};

int main()
{
    Car car1(100, "bmw");
    Car car2 = car1;
    car2.display();
    return 0;
}

