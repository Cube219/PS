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
    int n, l, k;
    cin >> n >> l >> k;
    vector<ll> d(n), a(n);
    for(auto& v : d) cin >> v;
    for(auto& v : a) cin >> v;

    vector<vector<ll>> dp(n, vector<ll>(k + 1, LNF));
    for(int i = 0; i <= k; ++i) {
        dp[0][i] = 0;
    }
    for(int i = 1; i < n; ++i) {
        for(int j = i - 1; j >= 0; --j) {
            int usek = i - j - 1;
            if(usek > k) break;

            for(int z = 0; z <= k; ++z) {
                if(usek + z > k) break;
                dp[i][usek + z] = min(dp[i][usek + z], dp[j][z] + a[j] * (d[i] - d[j]));
            }
        }
    }

    ll res = LNF;
    int uk = 0;
    for(int i = n - 1; i >= 0; --i) {
        for(int j = 0; j <= k; ++j) {
            if(uk + j > k) break;
            res = min(res, dp[i][j] + a[i] * (l - d[i]));
        }
        uk++;
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
