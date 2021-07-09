#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

using ll = long long int;
constexpr ll INF = 99999999999999;

struct Edge
{
    int u;
    int v;
    ll cost;
    ll rev;
};

struct GNode
{
    int nxt;
    ll cost;
    int eidx;
};

int n, m;
Edge e[50001];
vector<GNode> g[201];
ll dst[201][201];
ll dsttmp[201];
bool pathEdge[50001];

bool visit[201];
int past[201], pedge[201];

void dijk(int st, ll* _dst)
{
    for(int i = 0; i < n; ++i) {
        _dst[i] = INF;
        visit[i] = false;
        past[i] = -1;
        pedge[i] = -1;
    }
    _dst[st] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(visit[cur] == true) continue;

        visit[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.nxt;
            ll cost = nx.cost;

            if(visit[nxt] == false && _dst[nxt] > _dst[cur] + cost) {
                _dst[nxt] = _dst[cur] + cost;
                past[nxt] = cur;
                pedge[nxt] = nx.eidx;
                pq.push({ _dst[nxt], nxt });
            }
        }
    }
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
        int u, v;
        ll c, d;
        cin >> u >> v >> c >> d;
        u--; v--;
        e[i] = { u, v, c, d };
        g[u].push_back({ v, c, i });
    }

    for(int i = 0; i < n; ++i) {
        dijk(i, dst[i]);
        if(i == 0) {
            int cur = n - 1;
            while(past[cur] != -1) {
                pathEdge[pedge[cur]] = true;
                cur = past[cur];
            }
        } else if(i == n - 1) {
            int cur = 0;
            while(past[cur] != -1) {
                pathEdge[pedge[cur]] = true;
                cur = past[cur];
            }
        }
    }

    ll res = INF;
    res = min(res, dst[0][n - 1] + dst[n - 1][0]);

    for(int i = 0; i < m; ++i) {
        if(pathEdge[i] == true) {
            int u = e[i].u, v = e[i].v;
            for(int j = 0; j < g[u].size(); ++j) {
                if(g[u][j].eidx == i) {
                    g[u].erase(g[u].begin() + j);
                    break;
                }
            }
            g[v].push_back({ u, e[i].cost, i });

            dijk(0, dsttmp);
            ll cost = dsttmp[n - 1];
            dijk(n - 1, dsttmp);
            ll cost2 = dsttmp[0];
            res = min(res, cost + cost2 + e[i].rev);

            g[v].pop_back();
            g[u].push_back({ v, e[i].cost, i });
        } else {
            int u = e[i].u, v = e[i].v;
            ll cost = dst[0][v] + dst[u][n - 1] + e[i].cost;
            cost = min(cost, dst[0][n - 1]);

            ll cost2 = dst[n - 1][v] + dst[u][0] + e[i].cost;
            cost2 = min(cost2, dst[n - 1][0]);
            res = min(res, cost + cost2 + e[i].rev);
        }
    }

    if(res == INF) res = -1;
    cout << res << "\n";

    return 0;
}
