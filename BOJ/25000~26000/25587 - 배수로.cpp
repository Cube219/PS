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
    vector<int> par, sz, c, f;
    int res = 0;

    DSU(int _n) : n(_n), par(_n), sz(_n, 1), c(_n), f(_n)
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

        if(c[a] < f[a]) res -= sz[a];
        if(c[b] < f[b]) res -= sz[b];

        par[b] = a;
        sz[a] += sz[b];
        c[a] += c[b];
        f[a] += f[b];

        if(c[a] < f[a]) res += sz[a];

        return true;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        dsu.c[i] = a;
    }
    for(int i = 0; i < n; ++i) {
        int b;
        cin >> b;
        dsu.f[i] = b;
        if(dsu.c[i] < dsu.f[i]) dsu.res++;
    }

    for(int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            dsu.uni(x, y);
        } else {
            cout << dsu.res << "\n";
        }
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
