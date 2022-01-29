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
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<pair<int, ll>>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--; b--;
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }

    vector<ll> cycles, d(n, -1);
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        for(auto [nxt, w] : g[cur]) {
            if(nxt == pre) continue;

            if(d[nxt] != -1) {
                cycles.push_back(d[cur] ^ d[nxt] ^ w);
                continue;
            }

            d[nxt] = d[cur] ^ w;
            self(self, nxt, cur);
        }
    };
    d[0] = 0;
    dfs(dfs, 0, -1);

    vector<ll> basis(60, 0);
    for(ll v : cycles) {
        int mst = 60 - 1;
        while(v > 0) {
            while((v & (1LL << mst)) == 0) mst--;
            if(basis[mst] == 0) {
                basis[mst] = v;
                break;
            }
            v ^= basis[mst];
        }
    }

    for(int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;

        ll k = d[u] ^ d[v];
        for(int j = 60 - 1; j >= 0; --j) {
            if(k > (k ^ basis[j])) {
                k ^= basis[j];
            }
        }

        cout << k << "\n";
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
