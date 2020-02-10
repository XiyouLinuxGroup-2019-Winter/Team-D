#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("test.txt", ios::app);
    //直接把后面的作为参数传给这个对象的构造函数,
    //用ofstream类搞一个对象,对象的构造函数就是这个对象默认的函数
    //即open函数,不用out.open()
    //app在ios这个命名空间里
    if (!out) {
        cerr << "文件打开失败!" << endl;
        return 0;
    }
    for (int i = 10; i > 0; i--) {
        out << i;
    }

    out << endl;
    out.close();
    return 0;
}

