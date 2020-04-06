#include <iostream>
using namespace std;

int erjinzhi(int n, int *m) {
    int cnt = 0;
    for (int i = 0; i < 100; i++) {
        m[i] = n % 2;
        n /= 2;
        cnt++;
        if (n == 1) {
            i++;
            m[i] = 1;
            break;
        }
    }
    return cnt;
}

int main()
{
    int n;
    cin >> n;
    int m[100];
    while (n != 0) {
        int cnt = erjinzhi(n, m);
        for (int i = cnt; i >= 0; i--) {
            cout << m[i];
        } 
        cout << endl;
        cin >> n;
    }
    return 0;
}

