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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<char> visit(n, false);
    auto dfs = [&](auto&& self, int cur, int pre) -> int {
        visit[cur] = true;
        int ret = 1;
        for(int nxt : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            ret += self(self, nxt, cur);
        }
        return ret;
    };

    ll res = 1;
    for(int i = 0; i < n; ++i) {
        if(visit[i]) continue;

        int v = dfs(dfs, i, -1);
        res = (res * v) % MOD;
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
