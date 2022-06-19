#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <string>
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
    vector<vector<int>> g(n * m);
    string str;
    getline(cin, str);
    getline(cin, str);
    for(int i = 0; i < n; ++i) {
        getline(cin, str);
        int x = i;
        for(int j = 1; j < str.size(); ++j) {
            int y = (j - 1) / 2;
            int idx = x * m + y;

            if(j & 1) {
                // 아래
                if(str[j] == ' ') {
                    int nx = x + 1, ny = y;
                    if(nx >= n) continue;
                    int nidx = nx * m + ny;
                    g[idx].push_back(nidx);
                    g[nidx].push_back(idx);
                }
            } else {
                // 오른쪽
                if(str[j] == ' ') {
                    int nx = x, ny = y + 1;
                    if(ny >= m) continue;
                    int nidx = nx * m + ny;
                    g[idx].push_back(nidx);
                    g[nidx].push_back(idx);
                }
            }
        }
    }

    struct Point
    {
        int x, y;
    };
    int z;
    cin >> z;
    vector<Point> d(z);
    for(auto& v : d) {
        cin >> v.x >> v.y;
        v.x--; v.y--;
    }

    vector<vector<int>> par(n * m, vector<int>(22, -1));
    vector<int> dep(n * m, -INF);
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;
            par[nxt][0] = cur;
            dep[nxt] = dep[cur] + 1;
            self(self, nxt, cur);
        }
    };
    dep[0] = 0;
    dfs(dfs, 0, -1);

    for(int j = 1; j < 22; ++j) {
        for(int i = 0; i < n * m; ++i) {
            int tmp = par[i][j - 1];
            if(tmp != -1) par[i][j] = par[tmp][j - 1];
        }
    }

    auto lca = [&](int a, int b) {
        if(dep[a] > dep[b]) swap(a, b);
        int gap = dep[b] - dep[a];
        for(int i = 0; i < 22 && gap > 0; ++i, gap >>= 1) {
            if(gap & 1) b = par[b][i];
        }

        if(a != b) {
            for(int i = 22 - 1; i >= 0; --i) {
                if(par[a][i] != par[b][i] && par[a][i] != -1 && par[b][i] != -1) {
                    a = par[a][i];
                    b = par[b][i];
                }
            }
            a = par[a][0];
        }
        return a;
    };

    ll res = 0;
    int cur = d[0].x * m + d[0].y;
    for(int i = 1; i < d.size(); ++i) {
        int nxt = d[i].x * m + d[i].y;
        int g = lca(cur, nxt);
        res += dep[cur] + dep[nxt] - dep[g] * 2;
        cur = nxt;
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
