#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> m >> n;
    vector<vector<int>> dp(2, vector<int>(n + 1, -INF));
    dp[0][0] = dp[1][0] = 0;
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            // 0개
            // dp[1][j] = max(dp[1][j], dp[0][j]);
            // 1개
            dp[1][j] = max(dp[1][j], dp[0][j - 1] + 1);
            // 3개
            if(j >= 3) dp[1][j] = max(dp[1][j], dp[0][j - 3] + 2);
            // 7개
            if(j >= 7) dp[1][j] = max(dp[1][j], dp[0][j - 7] + 4);
            // 15개
            if(j >= 15) dp[1][j] = max(dp[1][j], dp[0][j - 15]);
        }
        swap(dp[0], dp[1]);
    }

    if(dp[0][n] < 0) dp[0][n] = -1;
    cout << dp[0][n];
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
