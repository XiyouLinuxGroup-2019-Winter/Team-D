#include <iostream>
using namespace std;

int main()
{
    int n, m;
    while (cin >> n >> m) {
        if (n == m == 0) {
            break;
        }
        int A[n], C[n];
        int b[n], dp[n];
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> C[i];
        }
         for (int i = 1; i <= n; i++)
        {
            int k = 1;
            while (k <= b[i])
            {
                for (int j = m; j >= k * a[i]; j--)
                {
                    dp[j] |= dp[j - k * a[i]];
                }
                b[i] -= k;
                k *= 2;
            }
            for (int j = m; j >= b[i] * a[i]; j--)
            {
                dp[j] |= dp[j - b[i] * a[i]];
            }
        }
    }
    return 0;
}

