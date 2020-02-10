#include <iostream>
using namespace std;

extern "C" void func() {

}

// 会产生错误
extern "C" void func(int v) {

}
int main()
{
    
    return 0;
}

