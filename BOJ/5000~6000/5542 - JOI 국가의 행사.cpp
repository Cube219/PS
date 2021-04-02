#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 2000000000;

int n, m, k, q;
vector<pair<int, int>> g[100001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[100001];
bool finish[100001];
struct Edge
{
    int u, v, w;
};
Edge e[200001];
int parent[100001], rnk[100001], dis[100001];

void dijk()
{
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(finish[cur] == true) continue;

        finish[cur] = true;

        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            int cost2 = nx.second;
            if(finish[nxt] == true) continue;
            if(d[nxt] > d[cur] + cost2) {
                d[nxt] = d[cur] + cost2;
                pq.push({ d[nxt], nxt });
            }
        }
    }
}

int find(int u)
{
    while(u != parent[u]) u = parent[u];
    return u;
}
void uni(int u, int v, int c)
{
    int ur = find(u);
    int vr = find(v);
    if(ur == vr) return;
    if(rnk[ur] > rnk[vr]) swap(ur, vr);
    parent[ur] = vr;
    if(rnk[ur] == rnk[vr]) rnk[vr]++;
    dis[ur] = c;
}
int query(int u, int v)
{
    int ret = 0;
    while(u != v) {
        if(dis[u] < dis[v]) swap(u, v);
        ret = dis[u];
        u = parent[u];
    }

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k >> q;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
        e[i] = { a, b, c };
    }
    for(int i = 1; i <= n; ++i) {
        d[i] = INF;
        dis[i] = -1;
    }
    for(int i = 0; i < k; ++i) {
        int a;
        cin >> a;
        pq.push({ 0, a });
        d[a] = 0;
    }
    dijk();

    for(int i = 0; i < m; ++i) {
        int u = e[i].u;
        int v = e[i].v;
        e[i].w = min(d[u], d[v]);
    }
    sort(e, e + m, [](const auto& l, const auto& r) {
        return l.w > r.w;
    });
    for(int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
    for(int i = 0; i < m; ++i) {
        uni(e[i].u, e[i].v, e[i].w);
    }

    for(int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        cout << query(u, v) << "\n";
    }

    return 0;
}
