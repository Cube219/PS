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
    vector<int> par, rnk;
    vector<double> dis;

    DSU(int _n) : n(_n), par(_n), rnk(_n, 1), dis(_n)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while(x != par[x]) x = par[x];
        return x;
    }

    bool uni(int a, int b, double w)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;

        if(rnk[a] < rnk[b]) swap(a, b);
        par[b] = a;
        dis[b] = w;
        if(rnk[a] == rnk[b]) rnk[a]++;
        return true;
    }

    double query(int a, int b)
    {
        double res = 10000000000;
        while(a != b) {
            if(dis[a] < dis[b]) swap(a, b);
            res = min(res, dis[a]);
            a = par[a];
        }

        return res;
    }
};


void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    for(auto& v : p) cin >> v.first >> v.second;

    vector<vector<int>> g(n);
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<double> dis(n * n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            int dx = abs(p[i].first - p[j].first);
            int dy = abs(p[i].second - p[j].second);
            dis[i * n + j] = sqrt(dx * dx + dy * dy);
        }
    }
    struct Edge
    {
        int u, v;
        double dis;
    };
    vector<Edge> eg;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;

            int cur = i * n + j;
            for(int nxti : g[i]) {
                int nxt = nxti * n + j;
                if(nxti == j || cur > nxt) continue;
                eg.push_back({ cur, nxt, min(dis[cur], dis[nxt]) });
            }
            for(int nxtj : g[j]) {
                int nxt = i * n + nxtj;
                if(nxtj == i || cur > nxt) continue;
                eg.push_back({ cur, nxt, min(dis[cur], dis[nxt]) });
            }
        }
    }

    sort(eg.begin(), eg.end(), [](const Edge& l, const Edge& r) {
        return l.dis > r.dis;
    });
    DSU dsu(n * n);
    for(auto& e : eg) {
        dsu.uni(e.u, e.v, e.dis);
    }

    cout.precision(8);
    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << fixed << dsu.query(a * n + b, b * n + a) << "\n";
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
