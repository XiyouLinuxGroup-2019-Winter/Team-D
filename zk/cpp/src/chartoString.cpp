#include <iostream>
#include <string>

using namespace std;

int main()
{
    const char *pszName = "liitdar";
    char pszCamp[] = "alliance";

    string strName;
    string strCamp;

    strName = pszName;
    strCamp = pszCamp;
    //将char* char[]转换为string类型时,直接
    //进行赋值操作,将char* char[]的变量赋值
    //给string对象即可.
    //这里的赋值实际上是将字符串的首地址赋值
    //给string对象了
    cout << strName << endl;
    cout << strCamp << endl;
    return 0;
}

