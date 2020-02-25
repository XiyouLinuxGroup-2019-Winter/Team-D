#include <iostream>
using namespace std;

class Point {
    friend Point operator+(const Point &, const Point &);
private:
    int m_x;
    int m_y;
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    void display() {
        cout << "(" << m_x << ", " << m_y << ")" << endl;
    }
};

Point operator+(const Point &p1, const Point &p2) {
    return Point(p1.m_x + p2.m_x, p1.m_y + p2.m_y);
}


int main()
{
    Point p1(10, 20);
    Point p2(20, 30);
    Point p3 = p1 + p2;
    // 本质是Point p3 = operator+(p1, p2);
    p3.display();
    Point p4 = p1 + p2 + p3;
    // 本质是调用了两次operator+, 第一次的结果又作为参数传进去
    p4.display();

    return 0;
}

