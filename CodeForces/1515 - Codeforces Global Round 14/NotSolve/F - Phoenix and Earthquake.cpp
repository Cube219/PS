#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

struct Edge
{
    int u, v;
    ll cost;
    int idx;
};
bool operator<(const Edge& l, const Edge& r)
{
    return l.cost < r.cost;
}

int n, m, x;
ll d[300001];
vector<pair<int, int>> g[300001];
int par[300001], sz[300001];
priority_queue<Edge> pq;
vector<int> res;

int find(int v)
{
    vector<int> st;
    while(par[v] != v) {
        st.push_back(v);
        v = par[v];
    }
    for(int t : st) {
        par[t] = v;
    }
    return v;
}
bool uni(int a, int b)
{
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) return false;
    if(sz[ra] < sz[rb]) swap(ra, rb);

    par[rb] = ra;
    d[ra] += d[rb] - x;
    sz[ra] += sz[rb];
    for(auto nx : g[ra]) {
        int nxt = nx.first;
        int idx = nx.second;
        if(par[nxt] != nxt || nxt == rb) continue;
        pq.push({ ra, nxt, d[ra] + d[nxt], idx });
    }
    for(auto nx : g[rb]) {
        int nxt = nx.first;
        int idx = nx.second;
        if(par[nxt] != nxt || nxt == ra) continue;
        g[ra].push_back({ nxt, idx });
        g[nxt].push_back({ ra, idx });
        pq.push({ ra, nxt, d[ra] + d[nxt], idx });
    }
    d[rb] = -99999999999999;
    sz[rb] = 0;
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> x;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        par[i] = i;
        sz[i] = 1;
    }
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({ v, i });
        g[v].push_back({ u, i });
        pq.push({ u, v, d[u] + d[v], i });
    }

    while(pq.size() > 0 && res.size() < n - 1) {
        Edge cur = pq.top();
        pq.pop();
        if(par[cur.u] != cur.u || par[cur.v] != cur.v) continue;
        if(cur.u == cur.v) continue;
        if(cur.cost != d[cur.u] + d[cur.v]) continue;
        if(cur.cost < x) {
            res.clear();
            break;
        }
        bool r = uni(cur.u, cur.v);
        if(r == true) res.push_back(cur.idx);
    }

    if(res.size() != n - 1) {
        cout << "NO";
    } else {
        cout << "YES\n";
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] + 1 << "\n";
        }
    }

    return 0;
}
