#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "输入形式:copyFile 原文件名 目标文件名\n";
        return 0;
    }
    ifstream in("argv[1]", ios::in | ios::binary);
    if (!in) {
        cout << "打开文件失败\n" << endl;
        return 0;
    }
    ofstream out("argv[2]", ios::out | ios::binary);
    if (!out) {
        cout << "打开文件失败\n" << endl;
        return 0;
    }
    int x;
    while (in >> x) {
        out << x;
    }
    out << endl;
    in.close();
    out.close();
    return 0;
}

