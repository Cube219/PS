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
    vector<int> a(n);
    int sumr = 0, sumb = 0;
    for(auto& v : a) {
        cin >> v;
        if(v == 0) sumr++;
        else sumb++;
    }
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<ll> res(n, 0);
    auto dfs = [&](auto&& self, int cur, int pre) -> pair<int, int> {
        int r = 0, b = 0;

        for(int nxt : g[cur]) {
            if(nxt == pre) continue;
            auto [cr, cb] = self(self, nxt, cur);

            res[cur] += (ll)r * cb;
            res[cur] += (ll)b * cr;

            r += cr;
            b += cb;
        }

        int outr = sumr - r, outb = sumb - b;
        if(a[cur] == 0) outr--;
        else outb--;;
        res[cur] += (ll)r * outb + (ll)b * outr;

        if(a[cur] == 0) r++;
        else b++;
        return { r, b };
    };
    dfs(dfs, 0, -1);
    
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int u;
        cin >> u;
        cout << res[u - 1] << "\n";
    }
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
