#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
struct Edge
{
    int u, v, w;
};
Edge e[100001];
int par[10001], r[10001], dis[10001];

int find(int v)
{
    while(par[v] != v) {
        v = par[v];
    }
    return v;
}
void uni(int u, int v, int w)
{
    int ur = find(u);
    int vr = find(v);
    if(ur == vr) return;
    if(r[ur] > r[vr]) swap(ur, vr);
    par[ur] = vr;
    if(r[ur] == r[vr]) r[vr]++;
    dis[ur] = w;
}
int query(int u, int v)
{
    int res = 2000000000;
    while(u != v) {
        if(dis[u] < dis[v]) swap(u, v);
        res = min(res, dis[u]);
        u = par[u];
    }

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        e[i] = { a, b, c };
    }

    sort(e, e + m, [](const auto& l, const auto& r) {
        return l.w > r.w;
    });
    for(int i = 1; i <= n; ++i) {
        par[i] = i;
    }
    for(int i = 0; i < m; ++i) {
        Edge& ed = e[i];
        uni(ed.u, ed.v, ed.w);
    }

    int st, ed;
    cin >> st >> ed;
    cout << query(st, ed);

    return 0;
}
