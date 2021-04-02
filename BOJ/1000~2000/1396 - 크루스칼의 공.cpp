#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, q;
struct Edge
{
    int u, v, w;
};
Edge e[100001];
int parent[100001], rnk[100001], dis[100001], sz[100001];
vector<int> c[100001], szSum[100001];
int cnt;

int find(int v)
{
    while(parent[v] != v) v = parent[v];
    return v;
}
void uni(int u, int v, int w)
{
    int ur = find(u);
    int vr = find(v);
    if(ur == vr) return;
    if(rnk[ur] > rnk[vr]) swap(ur, vr);
    parent[ur] = vr;
    c[vr].push_back(w);
    sz[vr] += sz[ur];
    szSum[vr].push_back(sz[vr]);
    if(rnk[ur] == rnk[vr]) rnk[vr]++;
    dis[ur] = w;
}
int query(int u, int v)
{
    if(find(u) != find(v)) return -1;
    int ret = 0;
    while(u != v) {
        if(dis[u] > dis[v]) swap(u, v);
        ret = dis[u];
        u = parent[u];
    }
    int idx = lower_bound(c[u].begin(), c[u].end(), ret) - c[u].begin();
    cnt = szSum[u][idx];
    return ret;
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
        return l.w < r.w;
    });

    for(int i = 1; i <= n; ++i) {
        dis[i] = 987654321;
        parent[i] = i;
        sz[i] = 1;
    }
    for(int i = 0; i < m; ++i) {
        uni(e[i].u, e[i].v, e[i].w);
    }

    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        int res = query(a, b);
        if(res != -1) {
            cout << res << " " << cnt << "\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
