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

int n, m;
struct Edge
{
    int dst, c, f, cost, revIdx;
};
vector<Edge> g[2005];
int pre[2005];
Edge* path[2005];
bool inq[2005];
int dis[2005];
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
pair<int, int> flow(int st, int ed)
{
    for(int i = 0; i < n * 2 + 2; ++i) {
        pre[i] = -1;
        inq[i] = false;
        dis[i] = 987654321;
    }
    queue<int> q;
    q.push(st);
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
                    inq[nxt] = true;
                }
            }
        }
    }
    if(pre[ed] == -1) return { 0, 0 };
    int flow = 987654321;
    int idx = ed;
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
pair<int, int> process(int st, int ed)
{
    pair<int, int> ret = { 0, 0 };
    for(int i = 0; i < 2; ++i) {
        auto r = flow(st, ed);
        ret.first += r.first;
        ret.second += r.second;
    }
    return ret;
}

void clear()
{
    for(int i = 0; i < n * 2 + 2; ++i) {
        g[i].clear();
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(cin.eof() == false) {
        cin >> n >> m;
        if(cin.eof() == true) break;
        for(int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            addEdge(a * 2 + 1, b * 2, 1, c);
        }
        for(int i = 0; i < n; ++i) {
            int c = 1;
            if(i == 0 || i == n - 1) c = 999;
            addEdge(i * 2, i * 2 + 1, c, 0);
        }
        int st = n * 2;
        int ed = st + 1;
        addEdge(st, 0, 2, 0);
        addEdge((n - 1) * 2 + 1, ed, 2, 0);

        auto res = process(st, ed);
        cout << res.second << "\n";

        clear();
    }

    return 0;
}
