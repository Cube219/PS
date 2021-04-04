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
vector<Edge> g[802];
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
int pre[802];
Edge* path[802];
bool inq[802];
int dis[802];
pair<int, int> flow(int st, int ed)
{
    for(int i = 0; i < n + m + 2; ++i) {
        pre[i] = -1;
        inq[i] = false;
        dis[i] = INF;
    }
    queue<int> q;
    q.push(st);
    inq[st] = true;
    dis[st] = 0;
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
    int cost = 0;
    idx = ed;
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
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int b, c;
            cin >> b >> c;
            b--;
            addEdge(i, n + b, 1, -c);
        }
    }

    for(int i = 0; i < n; ++i) {
        addEdge(st, i, 1, 0);
    }
    for(int i = 0; i < m; ++i) {
        addEdge(n + i, ed, 1, 0);
    }

    auto res = mcmf(st, ed);
    cout << res.first << "\n";;
    cout << -res.second;

    return 0;
}
