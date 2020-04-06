#include <iostream>
using namespace std;

int main()
{
    int n, m, z;
    int count = 0;
    cin >> n >> m >> z;
    for (int i = 1; i * m <= z; i++) {
        if ((i * m) % n == 0) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}

