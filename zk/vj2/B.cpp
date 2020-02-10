#include <iostream>
#include <cstring>
using namespace std;

int money[100];
double dp[100];
double p[100];

int main() {
    int T;
    cin >> T;
    while (T--) {
        memset(dp, 0, sizeof(dp));
        int bankCount;
        int sum = 0;
        double maxP;
        cin >> maxP >> bankCount;
        for (int i = 0; i < bankCount; i++) {
            cin >> money[i] >> p[i];
            sum += money[i];
        }
        for (int i = 0; i < bankCount; i++) {
            for (int j = sum; j >= money[i]; j--) {
                dp[j] = max(dp[j], dp[j-money[i]] * (1.0 - p[i]));
            }
        }
        for (int i = sum; i >= 0; i--) {
            if (maxP > (1 - dp[i])) {
                cin >> i;
                break;
            }
        }
    }
    return 0;
}
