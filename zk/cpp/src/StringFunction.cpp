#include <iostream>
#include <string>

#define HELLOSTR "Hello, World!"

using namespace std;

int main()
{
    string strOutput = "Hello, World!";
    // 用string类定义了一个对象
    // 这个对象有很多方法
    
    int nLen = strOutput.length();
    // 计算字符串长度的方法
    cout << "The length of strOutput is:" 
        << nLen << endl;
    if (strOutput.compare(HELLOSTR) == 0) {
        // 比较字符串的方法
        cout << "strOutput equal with macro HELLOSTR"
            << endl;
    }

    return 0;
}

