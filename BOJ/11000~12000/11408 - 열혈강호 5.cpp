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
    int d;
    int revIdx;
};
vector<Edge> g[805];
int pre[805];
Edge* path[805];
void addEdge(int st, int ed, int c, int d)
{
    Edge e1 = { ed, c, 0, d, -1 };
    Edge e2 = { st, 0, 0, -d, -1 };
    e1.revIdx = g[ed].size();
    e2.revIdx = g[st].size();
    g[st].push_back(e1);
    g[ed].push_back(e2);
}
void addFlow(Edge& e, int f)
{
    e.f += f;
    g[e.dst][e.revIdx].f -= f;
}

bool inq[805];
int dst[805];
pair<int, int> flow(int st, int ed)
{
    for(int i = 0; i < n + m + 2; ++i) {
        pre[i] = -1;
        inq[i] = false;
        dst[i] = INF;
    }
    queue<int> q;
    q.push(st);
    inq[st] = true;
    dst[st] = 0;
    while(q.empty() == false) {
        int cur = q.front();
        inq[cur] = false;
        q.pop();
        for(auto& nx : g[cur]) {
            int nxt = nx.dst;
            int c = nx.c;
            int f = nx.f;
            int d = nx.d;
            if(c > f && dst[nxt] > dst[cur] + d) {
                dst[nxt] = dst[cur] + d;
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
    int flow = INF;
    int cost = 0;
    while(idx != st) {
        flow = min(flow, path[idx]->c - path[idx]->f);
        idx = pre[idx];
    }
    idx = ed;
    while(idx != st) {
        addFlow(*path[idx], flow);
        cost += flow * path[idx]->d;
        idx = pre[idx];
    }
    return { flow, cost };
}

pair<int, int> maxflow(int st, int ed)
{
    pair<int, int> res = { 0, 0 };
    while(1) {
        pair<int, int> r = flow(st, ed);
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
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int b, c;
            cin >> b >> c;
            b--;
            addEdge(i, n + b, 1, c);
        }
    }
    int st = n + m;
    int ed = n + m + 1;
    for(int i = 0; i < n; ++i) {
        addEdge(st, i, 1, 0);

    }
    for(int i = 0; i < m; ++i) {
        addEdge(n + i, ed, 1, 0);
    }

    auto res = maxflow(st, ed);
    cout << res.first << "\n";
    cout << res.second;

    return 0;
}
