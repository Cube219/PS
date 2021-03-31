#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll INF = 9999999999999;

template <int N>
class Flow
{
public:
    struct Edge
    {
        int dst;
        ll c;
        ll f;
        int revIdx;
    };

    vector<Edge> g[N + 1];
    int pre[N + 1];
    Edge* path[N + 1];
    int n;

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
    }

    void addEdge(int s, int e, ll c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void addFlow(Edge& e, ll f)
    {
        e.f += f;
        g[e.dst][e.revIdx].f -= f;
    }

    ll flow(int st, int ed)
    {
        for(int i = 0; i <= n; ++i) {
            pre[i] = -1;
        }
        queue<int> q;
        q.push(st);
        while(q.empty() == false && pre[ed] == -1) {
            int cur = q.front();
            q.pop();
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                ll c = nx.c;
                ll f = nx.f;
                if(c > f && pre[nxt] == -1) {
                    pre[nxt] = cur;
                    path[nxt] = &nx;
                    q.push(nxt);
                    if(nxt == ed) break;
                }
            }
        }
        if(pre[ed] == -1) return 0;
        ll flow = INF;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        while(idx != st) {
            addFlow(*path[idx], flow);
            idx = pre[idx];
        }
        return flow;
    }

    ll maxFlow(int st, int ed)
    {
        ll res = 0;
        while(1) {
            ll f = flow(st, ed);
            if(f == 0) break;
            res += f;
        }

        return res;
    }
};


int n, m;
Flow<200101> f;
int sx, sy, st, ed;
int map[305][305];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i <= n + 1; ++i) {
        for(int j = 0; j <= m + 1; ++j) {
            map[i][j] = -1;
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            cin >> map[i][j];
        }
    }
    cin >> sx >> sy;
    sx++; sy++;
    f.init((n + 2) * (m + 2) * 2 + 2);
    // st = sx * (m + 2) + sy; st *= 2; st++;
    ed = (n + 2) * (m + 2) * 2;
    st = ed + 1;
    int tt = sx * (m + 2) + sy;
    f.addEdge(st, tt * 2, INF);

    for(int i = 0; i <= n + 1; ++i) {
        for(int j = 0; j <= m + 1; ++j) {
            int num = i * (m + 2) + j;
            if(map[i][j] != 0) {
                if(map[i][j] == -1) {
                    f.addEdge(num * 2, ed, INF);
                } else {
                    f.addEdge(num * 2, num * 2 + 1, map[i][j]);
                }
            }
            if(map[i][j] == -1) continue;
            for(int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n + 2 || ny >= m + 2) continue;
                if(map[nx][ny] == 0) continue;
                int nNum = nx * (m + 2) + ny;
                f.addEdge(num * 2 + 1, nNum * 2, INF);
            }
        }
    }
    ll res = f.maxFlow(st, ed);
    cout << res;

    return 0;
}
