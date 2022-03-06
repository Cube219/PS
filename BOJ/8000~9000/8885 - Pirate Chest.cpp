#define _CRT_SECURE_NO_WARNINGS
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
    vector<int> par, sz;

    DSU(int _n) : n(_n), par(_n), sz(_n, -1)
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
        return true;
    }

    int getsz(int x)
    {
        x = find(x);
        return sz[x];
    }
};

void solve()
{
    int a, b, n, m;
    cin >> a >> b >> n >> m;
    vector<vector<int>> d(n, vector<int>(m));
    for(auto& v1 : d) for(auto& v2 : v1) cin >> v2;

    ll res = 0;
    if(a > b) swap(a, b);
    int ab = max(a, b);

    struct Node
    {
        int v, idx;
    };
    vector<Node> tmp;
    for(int i = 0; i < n; ++i) {
        vector<Node> cur(m);
        for(int j = 0; j < m; ++j) {
            cur[j] = { INF, j };
        }

        for(int j = 0; j < ab; ++j) {
            if(i + j >= n) break;

            for(int k = 0; k < m; ++k) {
                cur[k].v = min(cur[k].v, d[i + j][k]);
            }

            tmp = cur;
            sort(tmp.begin(), tmp.end(), [](const Node& l, const Node& r) {
                return l.v < r.v;
            });

            DSU dsu(m);
            while(tmp.size() > 0) {
                Node c = tmp.back();
                tmp.pop_back();

                dsu.sz[c.idx] = 1;
                // merge left
                if(c.idx > 0 && dsu.sz[c.idx - 1] != -1) dsu.uni(c.idx - 1, c.idx);

                // merge right
                if(c.idx < m - 1 && dsu.sz[c.idx + 1] != -1) dsu.uni(c.idx, c.idx + 1);

                ll col = dsu.getsz(c.idx);
                if(j < a) col = min(col, (ll)b);
                else col = min(col, (ll)a);

                ll row = j + 1;
                ll h = c.v;

                ll newh = (h * n * m - 1) / ((ll)n * m - row * col);
                res = max(res, row * col * newh);
            }
        }
    }

    cout << res << "\n";
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
