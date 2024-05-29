#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
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
    DSU(int _n)
        : n(_n), par(_n)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while (x != par[x]) x = par[x] = par[par[x]];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        par[b] = a;
        return true;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    struct Edge
    {
        int u, v, l, r;
    };
    vector<Edge> eg(m);
    vector<int> vv;
    for (auto& v : eg) {
        cin >> v.u >> v.v >> v.l >> v.r;
        v.u--;
        v.v--;
        v.r++;
        vv.push_back(v.l);
        vv.push_back(v.r);
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    for (auto& v : eg) {
        v.l = lower_bound(vv.begin(), vv.end(), v.l) - vv.begin();
        v.r = lower_bound(vv.begin(), vv.end(), v.r) - vv.begin();
    }

    vector<int> reach(vv.size());
    for (int i = 0; i < vv.size(); ++i) {
        DSU dsu(n);
        for (auto [u, v, l, r] : eg) {
            if (l <= i && i < r) {
                dsu.uni(u, v);
            }

            reach[i] = (dsu.find(0) == dsu.find(n - 1)) ? 1 : 0;
        }
    }

    int k, res = 0;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int v;
        cin >> v;
        auto it = upper_bound(vv.begin(), vv.end(), v);
        if (it != vv.begin()) res += reach[prev(it) - vv.begin()];
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
