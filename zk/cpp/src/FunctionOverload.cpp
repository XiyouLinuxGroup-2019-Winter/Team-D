#include <iostream>

using namespace std;

double calc(double x);
double calc(double x, double y);
double calc(double x, double y, double z);

int main()
{
    double x, y, z;
    cin >> x >> y >> z;

    cout << calc(x) << '\n' << calc(x, y) 
        << '\n' << calc(x, y, z) << '\n' << endl;

    return 0;
}
double calc(double x) {
    return x * x;
}

double calc(double x, double y) {
    return x * y;
}

double calc(double x, double y, double z) {
    return x + y + z;
}

