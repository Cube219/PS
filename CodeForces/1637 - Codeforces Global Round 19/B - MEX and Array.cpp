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
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    ll res = 0;
    vector<int> has(201, 0);
    ll mex = 0;
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for(int r = 0; r < n; ++r) {
        mex = 0;
        for(int l = r; l >= 0; --l) {
            if(d[l] <= 200) {
                has[d[l]]++;
                while(has[mex] != 0) mex++;
            }
            for(int l2 = l; l2 >= 0; --l2) {
                ll v = mex + 1;
                if(l > 0) v += dp[l2][l - 1];
                dp[l2][r] = max(dp[l2][r], v);
            }
        }
        for(int l = r; l >= 0; --l) {
            if(d[l] <= 200) {
                has[d[l]] = 0;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            res += dp[i][j];
        }
    }

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
