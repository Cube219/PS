#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> dp2(1001, INF);

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> b(n), c(n);
    for(auto& v : b) cin >> v;
    for(auto& v : c) cin >> v;

    vector<int> cnt(n, 0);


    for(int i = 0; i < n; ++i) {
        cnt[i] = dp2[b[i]];
    }

    vector<ll> dp(k + 1, -1);
    dp[0] = 0;
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = k; j >= 0; --j) {
            if(j - cnt[i] < 0) break;
            if(dp[j - cnt[i]] != -1) {
                dp[j] = max(dp[j], dp[j - cnt[i]] + c[i]);
                res = max(res, dp[j]);
            }
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

    dp2[1] = 0;
    for(int i = 1; i <= 1000; ++i) {
        for(int j = i; j >= 1; --j) {
            int nxt = i + i / j;
            if(nxt > 1000) break;

            dp2[nxt] = min(dp2[nxt], dp2[i] + 1);
        }
    }

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
