#include <iostream>
#include <string>

using namespace std;

int main()
{
    string strDemo = "I am";

    strDemo.insert(2, " good.");
    //使用string类的insert方法,向字符串中
    //前面插入字符(串)
    cout << "strDemo is:" << strDemo << endl;

    return 0;
}

