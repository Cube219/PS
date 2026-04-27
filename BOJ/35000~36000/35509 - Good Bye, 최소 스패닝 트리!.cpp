#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#undef _LIBCPP_ENABLE_ASSERTIONS


#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct DSU
{
    int n;
    vector<int> par, sz;
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
        a = find(a); b = find(b);
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
        int u, v, w, idx;
    };
    vector<Edge> eg(m);
    for(int i = 0; i < m; ++i) {
        auto& v = eg[i];
        cin >> v.u >> v.v >> v.w;
        v.u--;
        v.v--;
        v.idx = i;
    }
    sort(eg.begin(), eg.end(), [](const auto& l, const auto& r)
    {
        return l.w < r.w;
    });

    int mx = -1;
    int cnt = 0;
    ll sum = 0;
    DSU dsu(n);
    for (auto& v : eg) {
        if (dsu.uni(v.u, v.v)) {
            mx = max(mx, v.w);
            cnt++;
            sum += v.w;
        }
        if (cnt == n - 1) break;
    }

    vector<Edge> newEg;
    for(int i = 0; i < m; ++i) {
        auto& v = eg[i];
        if (v.w <= mx) {
            newEg.push_back(v);
        }
    }

    DSU dsu2(n);
    ll sum2 = 0;
    vector<int> res;
    for (int i = newEg.size() - 1; i >= 0; --i) {
        auto& v = newEg[i];
        if (dsu2.uni(v.u, v.v)) {
            sum2 += v.w;
            res.push_back(v.idx);
        }
        if (res.size() == n - 1) break;
    }

    cout << "NO\n";
    if (sum == sum2) {
        cout<<"NO";
    } else {
        cout << "YES\n";
        for (int v : res) cout << v + 1 << "\n";
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
