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

struct Edge
{
    int dst, c, f, cost, revIdx;
};
vector<Edge> g[605];
int nodeNum;
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
int par[605];
Edge* path[605];
bool inq[605];
int dis[605];
pair<int, int> flow(int st, int ed)
{
    for(int i = 0; i < nodeNum; ++i) {
        par[i] = -1;
        dis[i] = INF;
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
                par[nxt] = cur;
                path[nxt] = &nx;
                if(inq[nxt] == false) {
                    q.push(nxt);
                    inq[nxt] = true;
                }
            }
        }
    }
    if(par[ed] == -1) return { 0, 0 };
    int idx = ed;
    int f = INF;
    while(idx != st) {
        f = min(f, path[idx]->c - path[idx]->f);
        idx = par[idx];
    }
    idx = ed;
    int cost = 0;
    while(idx != st) {
        addFlow(*path[idx], f);
        cost += path[idx]->cost * f;
        idx = par[idx];
    }
    return { f, cost };
}

int tNum;
int n, m;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            addEdge(i * 2, i * 2 + 1, 1, -1);
        }
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            addEdge(a * 2 + 1, b * 2, 1, 0);
        }
        int st = n * 2;
        int ed = st + 1;
        nodeNum = ed + 1;
        for(int i = 0; i < n; ++i) {
            addEdge(st, i * 2, 2, 0);
            addEdge(i * 2 + 1, ed, 2, 0);
        }

        int res = 0;
        for(int i = 0; i < 2; ++i) {
            auto r = flow(st, ed);
            res -= r.second;
        }
        cout << res << "\n";
        for(int i = 0; i < nodeNum; ++i) {
            g[i].clear();
        }
    }

    return 0;
}
