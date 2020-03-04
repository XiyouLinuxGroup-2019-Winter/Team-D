//使用string类的find方法, 在字符串中检索
//子字符串是否存在.
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string strOutput = "|0|1|2|";
    string strObj = "|1|";
    
    size_t nLoc = strOutput.find(strObj);
    // find方法的返回类型为size_t,
    // 如果检索到子串,返回子串在字符串
    // 中的位置,如果没有检索到,返回
    // string::npos
    if (nLoc != string::npos) {
        cout << nLoc << endl;
    }

    return 0;
}

