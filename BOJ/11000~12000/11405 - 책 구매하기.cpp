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

int n, m;
struct Edge
{
    int dst;
    int c;
    int f;
    int cost;
    int revIdx;
};
vector<Edge> g[205];
void addEdge(int s, int e, int c, int cost)
{
    Edge e1 = { e, c, 0, cost, -1 };
    Edge e2 = { s, 0, 0, -cost, -1 };
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
int pre[205];
Edge* path[205];
bool inq[205];
int dis[205];
pair<int, int> flow(int st, int ed)
{
    for(int i = 0; i < n + m + 2; ++i) {
        pre[i] = -1;
        dis[i] = INF;
        inq[i] = false;
    }
    queue<int> q;
    q.push(st);
    dis[st] = 0;
    inq[st] = false;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        inq[cur] = false;
        for(auto& nx : g[cur]) {
            int nxt = nx.dst;
            int c = nx.c;
            int f = nx.f;
            int cost = nx.cost;
            if(c > f && dis[nxt] > dis[cur] + cost) {
                dis[nxt] = dis[cur] + cost;
                pre[nxt] = cur;
                path[nxt] = &nx;
                if(inq[nxt] == false) {
                    inq[nxt] = true;
                    q.push(nxt);
                }
            }
        }
    }
    if(pre[ed] == -1) return { 0, 0 };
    int idx = ed;
    int flow = INF;
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
pair<int, int> maxFlow(int st, int ed)
{
    pair<int, int> res = { 0, 0 };
    while(1) {
        auto r = flow(st, ed);
        if(r.first == 0) break;
        res.first += r.first;
        res.second += r.second;
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
    int st = n + m;
    int ed = st + 1;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        addEdge(st, i, a, 0);
    }
    for(int i = 0; i < m; ++i) {
        int b;
        cin >> b;
        addEdge(n + i, ed, b, 0);
    }
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            int c;
            cin >> c;
            addEdge(j, n + i, INF, c);
        }
    }

    auto res = maxFlow(st, ed);
    cout << res.second;

    return 0;
}
