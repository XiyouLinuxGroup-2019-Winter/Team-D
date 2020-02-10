#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;
    cout << "please input string:";
    //string对象一旦初始化就不可变
    //例如:string str = "hello";
    getline(cin, str);
    cout << str;

    return 0;
}

