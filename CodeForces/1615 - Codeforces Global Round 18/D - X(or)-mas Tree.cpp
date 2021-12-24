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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    struct Input
    {
        int u, v, c;
    };
    vector<Input> in(n - 1);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, a;
        cin >> u >> v >> a;
        u--; v--;
        in[i] = { u, v, a };
        if(a != -1) {
            int cnt = 0;
            while(a > 0) {
                if(a & 1) cnt++;
                a >>= 1;
            }
            cnt %= 2;
            g[u].emplace_back(v, cnt);
            g[v].emplace_back(u, cnt);
        }
    }
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }

    vector<int> d(n, -1);
    bool res = true;
    auto dfs = [&](auto&& self, int cur, int color) -> void {
        d[cur] = color;
        for(auto [nxt, c] : g[cur]) {
            int newc = color ^ c;
            if(d[nxt] == -1) self(self, nxt, newc);
            else if(d[nxt] != newc) {
                res = false;
                break;
            }

            if(res == false) break;
        }
    };
    for(int i = 0; i < n; ++i) {
        if(d[i] == -1) {
            dfs(dfs, i, 0);
            if(res == false) break;
        }
    }

    if(res == false) cout << "NO\n";
    else {
        cout << "YES\n";
        for(auto& cur : in) {
            cout << cur.u + 1 << " " << cur.v + 1 << " ";
            int cost = cur.c;
            if(cost == -1) cost = d[cur.u] ^ d[cur.v];
            cout << cost << "\n";
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
