#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
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
    vector<int> h(n), s(n);
    for(int i = 0; i < n; ++i) {
        cin >> h[i] >> s[i];
    }

    vector<vector<ll>> group(n, vector<ll>(n));
    for(int i = 0; i < n; ++i) {
        ll hMx = -1, sSum = 0;
        for(int j = i; j < n; ++j) {
            if(hMx < h[j]) {
                hMx = h[j];
                sSum = 0;
            }
            if(hMx == h[j]) sSum += s[j];
            group[i][j] = sSum;
        }
    }

    vector<ll> dp(n);
    for(int i = 0; i < n; ++i) {
        dp[i] = group[0][i];
    }
    for(int i = 1; i < m; ++i) {
        vector<ll> ndp(n, 0);
        for(int j = i; j < n; ++j) {
            for(int k = i - 1; k < j; ++k) {
                ndp[j] = max(ndp[j], dp[k] + group[k + 1][j]);
            }
        }

        dp = move(ndp);
    }

    cout << dp[n - 1];
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
