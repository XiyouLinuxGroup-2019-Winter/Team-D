#include <iostream>
#include <fstream> //file stream 文件流头文件

using namespace std;

int main()
{
    ofstream out; //output file stream 输出文件流 文件写入类
    
    out.open("test.txt");//打开文件,从磁盘加载到内存
//  ofstream out("test.txt");
    if (!out) {
        cerr << "打开文件失败!" << endl;
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        out << i;
    }

    out << endl;
    out.close();

    return 0;
}

