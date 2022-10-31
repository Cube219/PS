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

struct DSU
{
    int n;
    vector<int> par, sz, cnt;

    DSU(int _n) : n(_n), par(_n), sz(_n, 1), cnt(_n, 0)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while(x != par[x]) x = par[x] = par[par[x]];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        par[b] = a;
        sz[a] += sz[b];
        cnt[a] += cnt[b];
        return true;
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    DSU dsu(n);
    for(int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        dsu.cnt[x - 1] = 1;
    }
    int c;
    cin >> c;

    vector<vector<pair<int, int>>> bccs;
    vector<int> dep(n, -1);
    int dNum;
    vector<char> isCut(n, false);
    vector<pair<int, int>> st;
    auto bcc_dfs = [&](auto&& self, int cur, int pre) -> int {
        dep[cur] = dNum++;
        int ret = dep[cur];
        int cNum = 0;

        for(int nxt : g[cur]) {
            if(nxt == pre) continue;

            if(dep[nxt] == -1 || dep[nxt] < dep[cur]) st.push_back({ cur, nxt });
            if(dep[nxt] == -1) {
                cNum++;
                int t = self(self, nxt, cur);
                if(t >= dep[cur]) {
                    if(dep[cur] > 0) isCut[cur] = true;

                    bccs.push_back({});
                    auto& bcc = bccs.back();
                    while(1) {
                        auto eg = st.back();
                        st.pop_back();
                        bcc.push_back(eg);

                        if(eg.first == cur) break;
                    }
                }
                ret = min(ret, t);
            } else ret = min(ret, dep[nxt]);
        }

        if(dep[cur] == 0 && cNum > 1) isCut[cur] = true;
        return ret;
    };

    for(int i = 0; i < n; ++i) {
        if(dep[i] == -1) {
            dNum = 0;
            bcc_dfs(bcc_dfs, i, -1);
        }
    }
    // bridges: bcc[i].size() == 1

    for(auto& b : bccs) {
        if(b.size() != 1) continue;

        dsu.uni(b[0].first, b[0].second);
    }

    int res = 0;
    vector<char> finish(n, false);
    for(int i = 0; i < n; ++i) {
        int v = dsu.find(i);
        if(finish[v]) continue;
        finish[v] = true;

        if(dsu.cnt[v] > 0) {
            res ^= dsu.sz[v] - dsu.cnt[v];
        }
    }
    if(res == 0) cout << 1 - c;
    else cout << c;
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
