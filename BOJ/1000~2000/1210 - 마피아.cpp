#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

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

    ll flow(int st, int ed, bool update = true)
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
        if(update == false) return 1;
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

    bool canFlow(int st, int ed)
    {
        return flow(st, ed, false) == 1;
    }
};

Flow<410> f;
int n, m, s, e;
vector<int> res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    f.init(n * 2 + 2);
    cin >> s >> e;
    s--; e--;
    int st = n * 2;
    int ed = n * 2 + 1;
    f.addEdge(st, s * 2, INF);
    f.addEdge(e * 2 + 1, ed, INF);
    for(int i = 0; i < n; ++i) {
        ll c;
        cin >> c;
        f.addEdge(i * 2, i * 2 + 1, c);
    }
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        f.addEdge(a * 2 + 1, b * 2, INF);
        f.addEdge(b * 2 + 1, a * 2, INF);
    }

    f.maxFlow(st, ed);

    for(int i = 0; i < n; ++i) {
        if(f.canFlow(st, i * 2) == true && f.canFlow(st, i * 2 + 1) == false) {
            res.push_back(i + 1);
        }
    }

    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
