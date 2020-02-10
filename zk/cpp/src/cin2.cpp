#include <iostream>

using namespace std;

int main()
{
    char str[20];

    cin.ignore(7);
    cin.getline(str, 10);

    cout << str << endl;//endl作用是清空缓冲区
    return 0;
}

