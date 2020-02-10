#include <iostream>

using namespace std;

int main()
{
    cout << "我可以格式化你的硬盘吗?\n" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        cout << "格式化中\n" << endl;
    }
    else if (answer == 'n' || answer == 'N') {
        cout << "不格式化\n" << endl; 
    }
    else {
        cout << "输入不合理\n" << endl;
    }

    return 0;
}

