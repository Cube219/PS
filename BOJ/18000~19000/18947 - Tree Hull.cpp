#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
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
    struct Nxt { int nxt, c; };
    vector<vector<Nxt>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g[u].push_back({ v, c });
        g[v].push_back({ u, c });
    }

    vector<vector<int>> par(n, vector<int>(20, -1));
    vector<int> idx(n), dep(n);
    vector<ll> cost(n);
    int num = 0;
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        idx[cur] = num++;
        for(auto [nxt, c] : g[cur]) {
            if(nxt == pre) continue;
            dep[nxt] = dep[cur] + 1;
            cost[nxt] = cost[cur] + c;
            par[nxt][0] = cur;
            self(self, nxt, cur);
        }
    };
    dep[0] = 0; cost[0] = 0;
    dfs(dfs, 0, -1);

    for(int j = 1; j < 20; ++j) {
        for(int i = 0; i < n; ++i) {
            int mid = par[i][j - 1];
            if(mid != -1) par[i][j] = par[mid][j - 1];
        }
    }
    auto lca = [&](int a, int b) {
        if(dep[a] < dep[b]) swap(a, b);
        for(int i = 0, g = dep[a] - dep[b]; g > 0; ++i, g >>= 1) {
            if(g & 1) a = par[a][i];
        }
        if(a != b) {
            for(int i = 20 - 1; i >= 0; --i) {
                if(par[a][i] != par[b][i]) {
                    a = par[a][i];
                    b = par[b][i];
                }
            }
            a = par[a][0];
        }
        return a;
    };

    ll res = 0;
    map<int, int> mp;
    auto process = [&](int v, bool isAdd) {
        if(!isAdd) {
            mp.erase(idx[v]);
            res -= cost[v];
        }

        if(mp.size() > 0) {
            auto rit = mp.upper_bound(idx[v]);
            if(rit == mp.end()) rit = mp.begin();
            auto lit = rit == mp.begin() ? prev(mp.end()) : prev(rit);
            
            int l = lit->second, r = rit->second;
            ll c = 0;
            if(l != r) c += cost[lca(l, r)];
            c -= cost[lca(l, v)] + cost[lca(v, r)];

            if(isAdd) res += c;
            else res -= c;
        }

        if(isAdd) {
            mp.insert({ idx[v], v });
            res += cost[v];
        }
    };

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        char t; int v;
        cin >> t >> v;
        v--;
        process(v, t == '+');
        if(mp.size() > 1) cout << res << "\n";
        else cout << "0\n";
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
