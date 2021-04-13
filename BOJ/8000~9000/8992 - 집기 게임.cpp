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

struct HEdge
{
    int x1, x2, y, w;
};
struct VEdge
{
    int y1, y2, x, w;
};

int tNum;
int n, m;
HEdge horizon[201];
VEdge vertical[201];

struct Edge
{
    int dst, c, f, cost, revIdx;
};
vector<Edge> g[805];
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

int pre[805];
Edge* path[805];
int dis[805];
bool inq[805];
pair<int, int> flow(int st, int ed)
{
    for(int i = 0; i < nodeNum; ++i) {
        pre[i] = -1;
        path[i] = nullptr;
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
                    inq[nxt] = true;
                }
            }
        }
    }
    if(pre[ed] == -1) return { 0, 0 };
    int idx = ed;
    int f = INF;
    while(idx != st) {
        f = min(f, path[idx]->c - path[idx]->f);
        idx = pre[idx];
    }
    int cost = 0;
    idx = ed;
    while(idx != st) {
        addFlow(*path[idx], f);
        cost += path[idx]->cost * f;
        idx = pre[idx];
    }
    return { f, cost };
}

bool iscross(const HEdge& h, const VEdge& v)
{
    if(v.x < h.x1 || h.x2 < v.x) return false;
    if(h.y < v.y1 || v.y2 < h.y) return false;
    return true;
}

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
            int x1, y1, x2, y2, w;
            cin >> x1 >> y1 >> x2 >> y2 >> w;
            if(x1 > x2) swap(x1, x2);
            horizon[i] = { x1, x2, y1, w };
            addEdge(i * 2, i * 2 + 1, 1, 0);
        }
        for(int i = 0; i < m; ++i) {
            int x1, y1, x2, y2, w;
            cin >> x1 >> y1 >> x2 >> y2 >> w;
            if(y1 > y2) swap(y1, y2);
            vertical[i] = { y1, y2, x1, w, };
            addEdge(n * 2 + i * 2, n * 2 + i * 2 + 1, 1, 0);
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(iscross(horizon[i], vertical[j])) {
                    addEdge(i * 2 + 1, n * 2 + j * 2, INF, -horizon[i].w * vertical[j].w);
                }
            }
        }
        int st = n * 2 + m * 2;
        int ed = st + 1;
        for(int i = 0; i < n; ++i) {
            addEdge(st, i * 2, INF, 0);
        }
        for(int i = 0; i < m; ++i) {
            addEdge(n * 2 + i * 2 + 1, ed, INF, 0);
        }
        nodeNum = ed + 1;

        int res = 0;
        int cnt = 0;
        while(1) {
            auto r = flow(st, ed);
            if(r.first == 0) break;
            res += r.second;
            cnt++;
        }
        cout << cnt << " " << -res << "\n";

        for(int i = 0; i < nodeNum; ++i) {
            g[i].clear();
        }
    }

    return 0;
}
