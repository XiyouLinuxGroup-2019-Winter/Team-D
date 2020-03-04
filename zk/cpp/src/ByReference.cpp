#include <iostream>

using namespace std;

void swap(int &x, int &y);

int main()
{
    int x, y;
    cin >> x >> y;

    swap(x, y);//会自动转换为地址

    cout << x << ' ' << y << '\n';
    return 0;
}

void swap(int &x, int &y) {
    int t;
    t = x;
    x = y;
    y = t;
}

