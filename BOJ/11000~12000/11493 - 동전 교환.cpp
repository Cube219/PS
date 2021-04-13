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
constexpr int INF = 987654321;

struct Edge
{
    int dst, c, f, cost, revIdx;
};
int tNum;
int n, m;
bool black[520], cblack[520];
vector<Edge> g[520];
void addEdge(int s, int e, int c, int cost)
{
    Edge e1 = { e, c, 0, cost, -1 };
    Edge e2 = { s, 0, 0, -cost, -1 };
    e1.revIdx = g[e].size();
    e2.revIdx = g[s].size();
    g[s].push_back(e1);
    g[e].push_back(e2);
}
void flow(Edge& e, int f)
{
    e.f += f;
    g[e.dst][e.revIdx].f -= f;
}

int pre[520];
Edge* path[520];
bool inq[520];
int dis[520];
pair<int, int> addFlow(int st, int ed)
{
    for(int i = 0; i < n + 2; ++i) {
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
    idx = ed;
    int cost = 0;
    while(idx != st) {
        flow(*path[idx], f);
        cost += path[idx]->cost * f;
        idx = pre[idx];
    }
    return { f, cost };
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
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            addEdge(a, b, INF, 1);
            addEdge(b, a, INF, 1);
        }
        for(int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            black[i] = (a == 0) ? true : false;
        }
        for(int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            cblack[i] = (a == 0) ? true : false;
        }
        int st = n;
        int ed = n + 1;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if(black[i] == true && cblack[i] == false) {
                addEdge(i, ed, 1, 0);
            } else if(black[i] == false && cblack[i] == true) {
                addEdge(st, i, 1, 0);
                cnt++;
            }
        }

        int res = 0;
        for(int i = 0; i < cnt; ++i) {
            auto t = addFlow(st, ed);
            res += t.second;
        }

        cout << res << "\n";

        for(int i = 0; i < n + 2; ++i) {
            g[i].clear();
        }
    }

    return 0;
}
