#include <iostream>
using namespace std;

inline void func() {
    cout << "123" << endl;
}

inline int sum(int v1, int v2) {
    return v1 + v2;
}

inline void run() {
    run();
}

int main()
{
    func();
    sum(1, 2);
     
    return 0;
}

