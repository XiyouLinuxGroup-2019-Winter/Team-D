#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1005;
int v[maxn];
int c[maxn];
long long dp[maxn][maxn];
int main()
{
    int n, T, s;
    cin >> T;
    while(T--) {
        memset(v, 0, sizeof(v));
        memset(c, 0, sizeof(c));
        memset(dp, 0, sizeof(dp));
        cin >> n >> s;
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= s; j++) {
                if (j < c[i]) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-c[i]]+v[i]);
                }
            }
        }
        cout << dp[n][s] << endl;
    }
    return 0;
}

