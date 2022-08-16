#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <queue>
#include <set>
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
    vector<set<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].insert(v);
        g[v].insert(u);
    }

    struct Res { int a, b, c, d; };
    vector<Res> res;

    auto update = [&](int a, int b, int c, int d) {
        g[a].erase(b); g[b].erase(a);
        g[b].erase(c); g[c].erase(b);
        g[c].erase(d); g[d].erase(c);

        g[a].insert(c); g[c].insert(a);
        g[a].insert(d); g[d].insert(a);
        g[b].insert(d); g[d].insert(b);

        res.push_back({ a + 1, b + 1, c + 1, d + 1 });
    };

    while(g[0].size() > 0) {
        vector<int> d;
        auto dfs = [&](auto&& self, int cur, int pre) -> void {
            d.push_back(cur);
            if(d.size() == 3) return;
            for(int nxt : g[cur]) {
                if(nxt == pre) continue;
                self(self, nxt, cur);
                if(d.size() == 3) return;
            }
            d.pop_back();
        };

        int nxt = *g[0].begin();
        dfs(dfs, nxt, 0);
        if(d.empty()) {
            g[0].erase(g[0].begin());
        } else {
            update(0, d[0], d[1], d[2]);
        }
    }

    cout << res.size() << "\n";
    for(auto [a, b, c, d] : res) cout << a << " " << b << " " << c << " " << d << "\n";
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
