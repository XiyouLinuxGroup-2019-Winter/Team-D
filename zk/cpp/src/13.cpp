#include <iostream>
using namespace std;

class Point {
private:
    static void test1() {
        cout << "Point::test1()" << endl;
    }
    static int ms_test2;
    int m_x;
    int m_y;
public:
    class Math {
    public:
        void test3() {
            cout << "Point::Math" << endl;
            test1();
            ms_test2 = 10;

            Point point;
            point.m_x = 10;
            point.m_y = 20;
        }
    };
};

int main()
{

    return 0;
}

