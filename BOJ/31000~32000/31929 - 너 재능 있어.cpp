#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> w(n);
    for (auto& v : w) cin >> v;
    int m;
    cin >> m;
    vector<int> l(m);
    for (auto& v : l) cin >> v;
    int k;
    cin >> k;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    dp[0][0] = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int mx = -INF;
            if (i > 0) mx = max(mx, dp[i - 1][j] + w[i - 1]);
            if (j > 0) {
                int kk = dp[i][j - 1] % k;
                if (kk <= 0) kk += k;
                mx = max(mx, dp[i][j - 1] - min(kk, l[j - 1]));
            }
            if (mx != -INF) dp[i][j] = mx;
        }
    }

    cout << dp[n][m];
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
