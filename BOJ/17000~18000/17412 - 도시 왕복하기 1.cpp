#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, p;

struct Edge
{
    int dst, c, f, revIdx;
};
vector<Edge> g[401];
void add(Edge& e, int f)
{
    e.f += f;
    g[e.dst][e.revIdx].f -= f;
}
int pre[401];
Edge* path[401];
queue<int> q;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> p;
    for(int i = 0; i < p; ++i) {
        int a, b;
        cin >> a >> b;
        Edge e1 = { b, 1, 0, -1 };
        Edge e2 = { a, 0, 0, -1 };
        e1.revIdx = g[b].size();
        e2.revIdx = g[a].size();
        g[a].push_back(e1);
        g[b].push_back(e2);
    }

    int st = 1, ed = 2;
    int res = 0;
    while(1) {
        while(q.empty() == false) q.pop();
        for(int i = 1; i <= n; ++i) {
            pre[i] = -1;
        }
        q.push(st);
        while(q.empty() == false && pre[ed] == -1) {
            int cur = q.front();
            q.pop();
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int c = nx.c;
                int f = nx.f;
                if(c - f > 0 && pre[nxt] == -1) {
                    pre[nxt] = cur;
                    path[nxt] = &nx;
                    q.push(nxt);
                    if(nxt == ed) break;
                }
            }
        }
        if(pre[ed] == -1) break;
        int flow = 987654321;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        while(idx != st) {
            add(*path[idx], flow);
            idx = pre[idx];
        }
        res += flow;
    }

    cout << res;

    return 0;
}
