#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
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
    vector<vector<ll>> mp(n * 2, vector<ll>(n * 2));
    for(auto& v1 : mp) {
        for(auto& v2 : v1) cin >> v2;
    }

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            res += mp[n + i][n + j];
        }
    }

    ll res2 = LNF;
    res2 = min(res2, mp[0][n]);
    res2 = min(res2, mp[0][n * 2 - 1]);
    res2 = min(res2, mp[n - 1][n]);
    res2 = min(res2, mp[n - 1][n * 2 - 1]);

    res2 = min(res2, mp[n][0]);
    res2 = min(res2, mp[n][n - 1]);
    res2 = min(res2, mp[n * 2 -1][0]);
    res2 = min(res2, mp[n * 2 - 1][n - 1]);

    cout << res + res2 << "\n";
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
