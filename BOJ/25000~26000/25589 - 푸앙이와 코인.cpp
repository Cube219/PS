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
    int n;
    cin >> n;
    vector<vector<ll>> d(n, vector<ll>(n));
    for(auto& v : d) for(auto& v2 : v) cin >> v2;

    vector<vector<ll>> sum = d;
    for(int i = 0; i < n; ++i) for(int j = 1; j < n; ++j) sum[i][j] += sum[i][j - 1];
    for(int j = 0; j < n; ++j) for(int i = 1; i < n; ++i) sum[i][j] += sum[i - 1][j];
    auto cal = [&](int x1, int y1, int x2, int y2) {
        ll res = sum[x2][y2];
        if(x1 > 0) res -= sum[x1 - 1][y2];
        if(y1 > 0) res -= sum[x2][y1 - 1];
        if(x1 > 0 && y1 > 0) res += sum[x1 - 1][y1 - 1];

        ll w = x2 - x1 + 1, h = y2 - y1 + 1;
        ll cnt = w * h;
        return res - cnt * cnt;
    };

    vector<vector<ll>> dp1(n, vector<ll>(n, -LNF));
    auto dp2 = dp1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i > 0) dp1[i][j] = max(dp1[i][j], dp1[i - 1][j]);
            if(j > 0) dp1[i][j] = max(dp1[i][j], dp1[i][j - 1]);
            int ri = n - i - 1, rj = n - j - 1;
            if(ri < n - 1) dp2[ri][rj] = max(dp2[ri][rj], dp2[ri + 1][rj]);
            if(rj < n - 1) dp2[ri][rj] = max(dp2[ri][rj], dp2[ri][rj + 1]);

            for(int k = min(i, j); k >= 0; --k) {
                dp1[i][j] = max(dp1[i][j], cal(i - k, j - k, i, j));
            }
            for(int k = min(n - ri, n - rj) - 1; k >= 0; --k) {
                dp2[ri][rj] = max(dp2[ri][rj], cal(ri, rj, ri + k, rj + k));
            }
        }
    }

    ll res = -LNF;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = min(i, j); k >= 0; --k) {
                ll v = -LNF;
                if(i - k > 0) v = max(v, dp1[i - k - 1][n - 1]);
                if(j - k > 0) v = max(v, dp1[n - 1][j - k - 1]);
                if(i < n - 1) v = max(v, dp2[i + 1][0]);
                if(j < n - 1) v = max(v, dp2[0][j + 1]);

                res = max(res, cal(i - k, j - k, i, j) + v);
            }
        }
    }

    cout << res;
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
