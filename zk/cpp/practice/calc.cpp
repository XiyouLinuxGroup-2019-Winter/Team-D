#include <iostream>
using namespace std;

int main()
{
    double num1, num2;
    char x;
    cin >> num1 >> x >> num2;
    switch (x) {
    case '+':
        cout << num1 + num2;
        break;
    case '-':
        cout << num1 - num2;
        break;
    case '*':
        cout << num1 * num2;
        break;
    case '/':
        if (num2 == 0) {
            cout << "operate error" << endl;
        }
        else {
            cout << num1 / num2;
        }
        break;
    case '%':
        if ((long)num2 == 0) {
            cout << "operate error" << endl; 
        }
        else {
            cout << (long)num1 % (long)num2;
        }
        break;
    default :
        cout << "operate error" << endl;
        break;
    }

    return 0;
}

