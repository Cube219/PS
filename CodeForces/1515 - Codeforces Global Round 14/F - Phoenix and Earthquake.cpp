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
priority_queue<pair<ll, int>> pq2;
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

    par[rb] = ra;
    return true;
}

bool uni2(int a, int b)
{
    int rb = find(b);
    int ra = find(a);
    if(ra == rb) return false;
    if(g[ra].size() < g[rb].size()) swap(ra, rb);
    par[rb] = ra;
    d[ra] += d[rb] - x;
    pq2.push({ d[ra], ra });

    for(auto nx : g[rb]) {
        int nxt = nx.first;
        int idx = nx.second;
        g[ra].push_back({ nxt, idx });
    }
    g[rb].clear();
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll sum = 0;
    cin >> n >> m >> x;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        sum += d[i];
        par[i] = i;
        sz[i] = 1;
        pq2.push({ d[i], i });
    }
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if(uni(u, v) == true) {
            g[u].push_back({ v, i });
            g[v].push_back({ u, i });
        }
    }

    for(int i = 1; i <= n; ++i) {
        par[i] = i;
    }

    while(pq2.size() > 0 && res.size() < n - 1) {
        int cur = pq2.top().second;
        ll cost = pq2.top().first;
        pq2.pop();
        if(par[cur] != cur || d[cur] != cost) continue;

        while(1) {
            if(g[cur].size() == 0) {
                break;
            }
            int nxt = g[cur].back().first;
            int idx = g[cur].back().second;
            nxt = find(nxt);
            if(cur == nxt) {
                g[cur].pop_back();
                continue;
            }
            g[cur].pop_back();
            res.push_back(idx);
            uni2(cur, nxt);
            break;
        }
    }

    if((ll)x * (ll)(n-1) > sum) {
        res.clear();
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
