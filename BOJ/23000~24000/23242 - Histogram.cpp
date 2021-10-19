#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
int d[4005], sum[4005], sum2[4005];
double dp[31][4005];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        sum[i] += d[i];
        sum[i + 1] = sum[i];
        sum2[i] += d[i] * d[i];
        sum2[i + 1] = sum2[i];
    }

    for(int i = 1; i <= n; ++i) {
        double avg = (double)(sum[i]) / i;
        double v = sum2[i];
        v -= 2.0 * (sum[i]) * avg;
        v += avg * avg * i;
        dp[0][i] = v;
    }

    double res = dp[0][n];
    for(int i = 1; i < m; ++i) {
        for(int j = 1; j <= n; ++j) {
            int cnt = 0;
            dp[i][j] = 999999999999;
            for(int k = j; k >= 1; --k) {
                cnt++;
                double avg = (double)(sum[j] - sum[k - 1]) / cnt;
                double v = sum2[j] - sum2[k - 1];
                v -= 2.0 * (sum[j] - sum[k - 1]) * avg;
                v += avg * avg * cnt;

                dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + v);
            }
        }
        res = min(res, dp[i][n]);
    }
    cout << fixed<< setprecision(6) << res;

    return 0;
}
