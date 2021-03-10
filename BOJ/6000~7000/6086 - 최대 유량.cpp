#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n;

struct Edge
{
    int dst, c, f;
    int revIdx;
};
vector<Edge> g[1001];

void add(Edge& e, int cost)
{
    e.f += cost;
    g[e.dst][e.revIdx].f -= cost;
}

int pre[1001];
Edge* path[1001];
queue<int> q;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        char a, b;
        int c;
        cin >> a >> b >> c;

        int u = a - 'A';
        int v = b - 'A';

        Edge e1 = { v, c, 0, -1 };
        Edge e2 = { u, c, 0, -1 };
        e1.revIdx = g[v].size();
        e2.revIdx = g[u].size();

        g[u].push_back(e1);
        g[v].push_back(e2);
    }

    int res = 0;
    int st = 0, ed = 'Z' - 'A';
    while(1) {
        for(int i = 0; i < 'z' - 'A' + 1; i++) {
            pre[i] = -1;
        }
        while(q.empty() == false) q.pop();
        q.push(st);
        while(q.empty() == false && pre[ed] == -1) {
            int cur = q.front();
            q.pop();

            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int c = nx.c;
                int f = nx.f;
                if(c - f > 0 && pre[nxt] == -1) {
                    q.push(nxt);
                    pre[nxt] = cur;
                    path[nxt] = &nx;
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
