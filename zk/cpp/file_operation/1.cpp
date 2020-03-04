#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream in;//input file stream输入文件流,是文件读取类
    in.open("test.txt");
    //或
//  ifstream in("test.txt");
    if (!in) {
        cerr << "打开文件失败" << endl;
        return 0;
    }
    char x;
    while (in >> x) {
        cout << x;
    }
    cout << endl;
    in.close();

    return 0;
}

