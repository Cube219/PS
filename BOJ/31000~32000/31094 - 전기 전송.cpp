#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
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
    struct Edge
    {
        int nxt, r, z;
    };
    vector<vector<Edge>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, r, z;
        cin >> u >> v >> r >> z;
        u--;
        v--;
        g[u].push_back({v, r, z});
        g[v].push_back({u, r, z});
    }

    vector<vector<int>> par(n, vector<int>(20, -1));
    vector<vector<int>> two(n, vector<int>(20, 0));
    vector<ll> sum(n, 0);
    vector<int> zz(n, 0);
    vector<int> depth(n, 0);
    auto dfs = [&](auto&& self, int cur, int dep) -> void {
        depth[cur] = dep;
        for (auto [nxt, r, z] : g[cur]) {
            if (depth[nxt] == 0) {
                par[nxt][0] = cur;
                if (z > 1) two[nxt][0] = 1;
                sum[nxt] = sum[cur] + r;
                zz[nxt] = z;
                self(self, nxt, dep + 1);
            }
        }
    };
    dfs(dfs, 0, 1);

    for (int i = 0; i < 20 - 1; ++i) {
        for (int j = 0; j < n; ++j) {
            if (par[j][i] != -1) {
                par[j][i + 1] = par[par[j][i]][i];
                two[j][i + 1] = two[j][i] + two[par[j][i]][i];
            } else {
                two[j][i + 1] = two[j][i];
            }
        }
    }

    struct Res
    {
        int lca;
        int twoSum;
    };
    auto lcaQuery = [&](int a, int b) -> Res {
        Res res;
        res.twoSum = 0;

        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        int gap = depth[b] - depth[a];
        int idx = 0;
        while (gap > 0) {
            if (gap % 2 == 1) {
                res.twoSum += two[b][idx];
                b = par[b][idx];
            }
            idx++;
            gap /= 2;
        }

        if (a != b) {
            for (int j = 20 - 1; j >= 0; j--) {
                if (par[a][j] != 0 && par[b][j] != 0 && par[a][j] != par[b][j]) {
                    res.twoSum += two[a][j];
                    a = par[a][j];
                    res.twoSum += two[b][j];
                    b = par[b][j];
                }
            }

            res.twoSum += two[a][0];
            res.twoSum += two[b][0];
            a = par[a][0];
        }

        res.lca = a;
        return res;
    };

    auto closest = [&](int a) {
        for (int i = 20 - 1; i >= 0; i--) {
            if (two[a][i] == 0) {
                a = par[a][i];
            }
            if (a == -1) break;
        }
        if (a == -1) return -1;
        if (two[a][0] > 0) return a;
        else return -1;
    };

    int qNum;
    cin >> qNum;
    for (int i = 0; i < qNum; ++i) {
        int a, b;
        ll e;
        cin >> a >> b >> e;
        a--;
        b--;

        auto RR = lcaQuery(a, b);
        int twoSum = RR.twoSum;
        int lca = RR.lca;

        if (twoSum > 64) {
            cout << "0\n";
            continue;
        }

        int cur = a;

        vector<int> up, down;
        while (1) {
            int nxt = closest(cur);
            if (nxt == -1 || depth[nxt] <= depth[lca]) break;

            up.push_back(nxt);
            cur = par[nxt][0];
            if (cur == -1) break;
        }
        cur = b;
        while (1) {
            int nxt = closest(cur);
            if (nxt == -1 || depth[nxt] <= depth[lca]) break;

            down.push_back(nxt);
            cur = par[nxt][0];
            if (cur == -1) break;
        }
        reverse(down.begin(), down.end());

        ll res = e;
        cur = a;
        for (int nxt : up) {
            res -= sum[cur] - sum[nxt];
            int nnxt = par[nxt][0];
            // if (nnxt == -1 || depth[nnxt] < depth[lca]) break;

            res = (ll)((res - (sum[nxt] - sum[nnxt])) / zz[nxt]);

            cur = nnxt;
        }
        res -= sum[cur] - sum[lca];

        cur = lca;
        for (int nxt : down) {
            int nnxt = par[nxt][0];
            res -= sum[nnxt] - sum[cur];
            res = (ll)((res - (sum[nxt] - sum[nnxt])) / zz[nxt]);
            cur = nxt;
        }
        res -= sum[b] - sum[cur];

        cout << max(0LL, res) << "\n";
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
