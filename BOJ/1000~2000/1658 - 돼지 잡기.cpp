#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

template<int N>
class Flow
{
public:
    struct Edge
    {
        int dst, c, f, revIdx;
    };
    vector<Edge> g[N + 1];
    int pre[N + 1];
    Edge* path[N + 1];

    void addEdge(int s, int e, int c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
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

    int flow(int st, int ed)
    {
        for(int i = 0; i <= N; ++i) {
            pre[i] = -1;
        }
        queue<int> q;
        q.push(st);
        while(q.empty() == false && pre[ed] == -1) {
            int cur = q.front();
            q.pop();
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int c = nx.c;
                int f = nx.f;
                if(c > f && pre[nxt] == -1) {
                    pre[nxt] = cur;
                    path[nxt] = &nx;
                    q.push(nxt);
                    if(nxt == ed) break;
                }
            }
        }
        if(pre[ed] == -1) return 0;
        int flow = 987654321;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        while(idx != st) {
            addFlow(*path[idx], flow);
            idx = pre[idx];
        }
        return flow;
    }

    int maxFlow(int st, int ed)
    {
        int res = 0;
        while(1) {
            int f = flow(st, ed);
            if(f == 0) break;
            res += f;
        }

        return res;
    }
};

Flow<110000> f;
int n, m;
int d[1001];
int req[101];
bool has[1001];

constexpr int INF = 987654321;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    int pSt = n * m + 1;
    int st = pSt + m * 2;
    int ed = st + 1;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        f.addEdge(st, i, d[i]);
    }
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            has[j] = false;
        }
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int key;
            cin >> key;
            key--;
            has[key] = true;
        }
        for(int j = 0; j < n; ++j) {
            if(has[j] == true) {
                f.addEdge(i * n + j, pSt + (i * 2), INF);
                if(i == m - 1) continue;
                f.addEdge(i * n + j, pSt + (i * 2 + 1), INF);
                f.addEdge(pSt + (i * 2 + 1), (i + 1) * n + j, INF);
            } else {
                if(i == m - 1) continue;
                f.addEdge(i * n + j, (i + 1) * n + j, INF);
            }
        }
        cin >> req[i];
        f.addEdge(pSt + (i * 2), ed, req[i]);
    }

    cout << f.maxFlow(st, ed);

    return 0;
}
