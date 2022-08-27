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
    vector<vector<int>> g(n);
    for(int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dep(n, -1); int dNum = 0;
    vector<int> par(n, -1);
    int c1, c2;
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        dep[cur] = dNum++;
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;
            if(dep[nxt] == -1) {
                par[nxt] = cur;
                self(self, nxt, cur);
            } else {
                c1 = nxt;
                c2 = cur;
            }
        }
    };
    dfs(dfs, 0, -1);

    vector<char> isCycle(n, false);
    while(c1 != c2) {
        isCycle[c1] = true;
        isCycle[c2] = true;
        if(dep[c1] > dep[c2]) c1 = par[c1];
        else if(dep[c1 < dep[c2]]) c2 = par[c2];
        else {
            c1 = par[c1];
            c2 = par[c2];
        }
    }
    isCycle[c1] = true;

    vector<int> color(n, -1); int cNum = 0;
    auto dfs2 = [&](auto&& self, int cur, int pre) -> void {
        color[cur] = cNum;
        for(int nxt : g[cur]) {
            if(nxt == pre || color[nxt] != -1 || isCycle[nxt]) continue;
            self(self, nxt, cur);
        }
    };
    for(int i = 0; i < n; ++i) {
        if(!isCycle[i]) continue;
        dfs2(dfs2, i, -1);
        cNum++;
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if(color[u] == color[v]) cout << "Yes\n";
        else cout << "No\n";
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
