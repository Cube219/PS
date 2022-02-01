#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
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
    vector<int> par;
    DSU(int _n) : n(_n), par(_n)
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
        return true;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    struct Edge
    {
        int u, v, w;
    };
    vector<Edge> eg(m);
    for(auto& v : eg) {
        cin >> v.u >> v.v >> v.w;
        v.u--; v.v--;
    }

    vector<int> vv;
    vv.push_back(0);
    for(int i = 0; i < m; ++i) {
        for(int j = i; j < m; ++j) {
            vv.push_back((eg[i].w + eg[j].w + 1) / 2);
        }
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());

    auto mst = [&](int k) {
        sort(eg.begin(), eg.end(), [k](const Edge& l, const Edge& r) {
            return abs(l.w - k) < abs(r.w - k);
        });

        ll res = 0;
        DSU dsu(n);
        for(auto& v : eg) {
            if(dsu.uni(v.u, v.v)) {
                res += abs(v.w - k);
            }
        }
        return res;
    };
    vector<ll> d(vv.size()), d2(vv.size());
    for(int i = 0; i < vv.size(); ++i) {
        d[i] = mst(vv[i]);
        d2[i] = mst(vv[i] + 1);
    }

    ll p, k, a, b, c;
    cin >> p >> k >> a >> b >> c;
    ll q;
    ll res = 0;
    for(int i = 0; i < k; ++i) {
        if(i < p) cin >> q;
        else q = (q * a + b) % c;

        auto idx = upper_bound(vv.begin(), vv.end(), q) - vv.begin() - 1;

        res ^= d[idx] + (d2[idx] - d[idx]) * (q - vv[idx]);
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
