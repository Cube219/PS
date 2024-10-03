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
    ll n, m, k, r, w;
    cin >> n >> m >> k >> r >> w;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> d(n);
    for (auto& v : d) cin >> v;

    ll res = 0;

    auto cal = [&](int u, int v, ll cnt) -> ll {
        if (cnt > k || cnt < 0) return -LNF;

        ll res = d[u] * (cnt / 2) + d[v] * ((cnt + 1) / 2);
        res += cnt / r * w;
        return res;
    };

    for(int i = 0; i < n; ++i) {
        ll mx = -LNF;

        int u = i, v = -1;
        ll vVal = -LNF;
        for(int nxt : g[u]) {
            if (vVal < d[nxt]) {
                vVal = d[nxt];
                v = nxt;
            }
        }

        if (v != -1) {
            mx = max(mx, cal(u, v, 0));
            mx = max(mx, cal(u, v, 1));
            mx = max(mx, cal(u, v, 2));

            mx = max(mx, cal(u, v, r));
            mx = max(mx, cal(u, v, r - 1));
            mx = max(mx, cal(u, v, r - 2));
            // mx = max(mx, cal(u, v, r + 1));
            // mx = max(mx, cal(u, v, r + 2));

            // mx = max(mx, cal(u, v, r * 2));
            mx = max(mx, cal(u, v, r * 2 - 1));
            // mx = max(mx, cal(u, v, r * 2 - 2));
            // mx = max(mx, cal(u, v, r * 2 + 1));
            // mx = max(mx, cal(u, v, r * 2 + 2));

            mx = max(mx, cal(u, v, k));
            mx = max(mx, cal(u, v, k - 1));
            // mx = max(mx, cal(u, v, k - 2));

            mx = max(mx, cal(u, v, k / r * r));
            mx = max(mx, cal(u, v, k / r * r + 1));
            // mx = max(mx, cal(u, v, k / r * r + 2));
            mx = max(mx, cal(u, v, k / r * r - 1));
            mx = max(mx, cal(u, v, k / r * r - 2));

            mx = max(mx, cal(u, v, k / r * r - r));
            mx = max(mx, cal(u, v, k / r * r - r + 1));
            // mx = max(mx, cal(u, v, k / r * r - r + 2));
            mx = max(mx, cal(u, v, k / r * r - r - 1));
            // mx = max(mx, cal(u, v, k / r * r - r - 2));

            res = max(res, mx);
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
