#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

template <int N>
class MCMF
{
public:
    struct Edge
    {
        int dst;
        int c;
        int f;
        int cost;
        int revIdx;
    };

    vector<Edge> g[N + 1];
    int pre[N + 1];
    Edge* path[N + 1];
    bool inQ[N + 1];
    int dis[N + 1];
    int n;

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
    }

    void addEdge(int s, int e, int c, int cost, bool biDir = false)
    {
        Edge e1 = { e, c, 0, cost, -1 };
        Edge e2 = { s, 0, 0, -cost, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void addFlow(Edge& e, int f)
    {
        e.f += f;
        g[e.dst][e.revIdx].f -= f;
    }

    pair<int, int> flow(int st, int ed)
    {
        for(int i = 0; i <= n; ++i) {
            pre[i] = -1;
            inQ[i] = false;
            dis[i] = INF;
        }
        queue<int> q;
        q.push(st);
        inQ[st] = true;
        dis[st] = 0;
        while(q.empty() == false) {
            int cur = q.front();
            q.pop();
            inQ[cur] = false;
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int c = nx.c;
                int f = nx.f;
                int cost = nx.cost;
                if(c > f && dis[nxt] > dis[cur] + cost) {
                    dis[nxt] = dis[cur] + cost;
                    pre[nxt] = cur;
                    path[nxt] = &nx;
                    if(inQ[nxt] == false) {
                        q.push(nxt);
                        inQ[nxt] = true;
                    }
                }
            }
        }
        if(pre[ed] == -1) return { 0, 0 };
        int flow = INF;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        int cost = 0;
        while(idx != st) {
            addFlow(*path[idx], flow);
            cost += path[idx]->cost * flow;
            idx = pre[idx];
        }
        return { flow, cost };
    }

    pair<int, int> mcmf(int st, int ed)
    {
        pair<int, int> res = { 0, 0 };
        while(1) {
            pair<int, int> f = flow(st, ed);
            if(f.first == 0) break;
            res.first += f.first;
            res.second += f.second;
        }

        return res;
    }
};

int n, m;
MCMF<204> mcmf;
pair<int, int> d[101][101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    mcmf.init(n + m + 2);
    int st = n + m;
    int ed = st + 1;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        mcmf.addEdge(st, i, a, 0);
    }
    for(int i = 0; i < m; ++i) {
        int b;
        cin >> b;
        mcmf.addEdge(n + i, ed, b, 0);
    }
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> d[i][j].first;
        }
    }
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> d[i][j].second;
        }
    }

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            mcmf.addEdge(j, n + i, d[i][j].first, d[i][j].second);
        }
    }

    auto res = mcmf.mcmf(st, ed);
    cout << res.first << "\n";
    cout << res.second;

    return 0;
}
