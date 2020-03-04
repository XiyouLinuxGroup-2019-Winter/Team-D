#include <iostream>

using namespace std;

int main()
{
    const int ITEM = 10;
    int num[ITEM];
    int sum = 0;
    double ave = 0;
    for (int i = 0; i < ITEM; i++) {
        while (!(cin >> num[i])) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "please input right data:";

        } //cin当输入错误时返回0
        
        sum += num[i];
    }
    ave = (double)sum / ITEM;
    cout << sum << '\n' << ave << endl;
    return 0;
}

