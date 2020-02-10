#include <iostream>

using namespace std;

int main()
{
    int sum = 0;
    cout << "请输入一串整数和任意数目的空格:";
    
    int i;
    while (cin >> i) {
        sum += i;
        while  (cin.peek() == ' ') {
            cin.get();
        }
        if (cin.peek() == '\n') {
            break;
        }
    }
    cout << "结果是:" << sum << endl;
    return 0;
}

