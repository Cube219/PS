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
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<vector<long double>>> dp(2);
    dp[0].resize(n, vector<long double>(2, 0));
    dp[1].resize(n, vector<long double>(2, 0));
    long double divisor = 3;
    for(int i = 0; i < n; ++i) {
        dp[0][i][0] = 2.0 / divisor;
        divisor *= 3;
    }
    for(int i = 1; i < m; ++i) {
        long double sum = 0;
        for(int j = 0; j < n; ++j) {
            if(j > 0) {
                sum += dp[0][j - 1][0] / 3.0;
                sum += dp[0][j - 1][1] * 2.0 / 3.0;
            }
            dp[1][j][0] = sum;
            dp[1][j][1] = dp[0][j][0] / 2.0;
            sum /= 3.0;
        }

        swap(dp[0], dp[1]);
    }

    long double res = 1;
    for(int i = 0; i < n; ++i) {
        res -= dp[0][i][0] + dp[0][i][1];
    }
    cout << fixed << setprecision(10) << res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
