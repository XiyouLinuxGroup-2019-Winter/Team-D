//string 转换为char*
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string strOutput = "Hello World";
    //cout 可以直接输出string类的对象的内容
    cout << "[cout] strOutput is:"
        << strOutput << endl;
    //string 转换为char*
    const char *pszOutput = strOutput.c_str();
    //因为string对象一旦初始化就不可变
    //所以要加const
    //c_str()方法和data()方法在c++11版本中一样
    printf("[printf] strOutput is:%s\n"
           , pszOutput);
    //printf()函数不能直接打印string类的
    //对象的内容,可以通过将string转换为
    //char*类型,在使用printf()函数打印
    return 0;
}

