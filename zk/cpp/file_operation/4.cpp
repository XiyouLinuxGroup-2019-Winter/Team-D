#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream fp("test.txt", ios::in | ios::out);
    if (!fp) {
        cerr << "打开文件失败!" << endl;
        return 0;
    }

    fp << "hello,world!12";

    static char str[20];

    fp.seekg(ios::beg);//使得文件指针指向文件头,ios::end则是文件尾
    fp >> str;
    cout << str << endl;
    fp.close();
    return 0;
}

