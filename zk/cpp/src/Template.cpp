#include <iostream>

using namespace std;

template <typename elemType> 
//定义一个模版

void print(elemType *pBegin, elemType *pEnd) {
    while (pBegin != pEnd) {
        cout << *pBegin;
        pBegin++;
    }
}

int main()
{
    int num[5] = {0, 1, 2, 3, 4};
    char name[5] = {'F', 'i', 's', 'h', 'C'};

    print(num, num+5);
    cout << '\n';
    print(name, name+5);
    cout << '\n';

    return 0;
}

