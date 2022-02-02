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
    DSU dsu(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        dsu.uni(a, b);
    }

    int cur = -1;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        a--;

        a = dsu.find(a);
        if(cur != -1 && cur != a) {
            res++;
        }
        cur = a;
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
