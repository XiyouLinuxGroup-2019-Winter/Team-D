#include <iostream>

using namespace std;

int main()
{
    char p;
    cout << "请输入一段文本:\n";
    
    while (cin.peek() != '\n') {
        p = cin.get();
        cout << p;
    }
    cout << endl;
    return 0;
}

