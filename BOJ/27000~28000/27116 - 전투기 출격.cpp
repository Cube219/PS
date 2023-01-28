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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(m, vector<int>(m));
    for(auto& v : g) for(auto& v2 : v) cin >> v2;
    vector<int> f(m), a(n);
    for(auto& v : f) cin >> v;
    for(auto& v : a) {
        cin >> v;
        v--;
    }

    for(int k = 0; k < m; ++k) {
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < m; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    vector<ll> d(n * 2 + 1, 0);
    int last = 0;
    for(int i = 0; i < n; ++i) {
        d[i] = g[last][a[i]];
        last = a[i];
    }

    auto ck = [&](int x) {
        ll res = LNF;

        ll preSum = 0, postSum = accumulate(d.begin() + x + 1, d.end(), 0LL);
        for(int i = 0; i < n; ++i) {
            preSum += d[i];
            postSum -= d[i + x + 1];

            ll v = preSum + postSum + f[a[i]];
            if(i + x + 1 < n) v += g[a[i]][a[i + x + 1]];
            if(v <= k) res = min(res, v);
        }

        return res;
    };

    int lo = -1, hi = n + 1;
    ll res = LNF;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        ll use = ck(mid);
        if(use < LNF) {
            hi = mid;
            res = use;
        } else {
            lo = mid;
        }
    }

    if(hi == n + 1) cout << "-1";
    else cout << hi << " " << res;
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
