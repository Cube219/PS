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

template <int N>
class Flow
{
public:
    struct Edge
    {
        int dst;
        int c;
        int f;
        int revIdx;
    };

    vector<Edge> g[N + 1];
    int pre[N + 1];
    Edge* path[N + 1];
    int n;

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
    }

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
        for(int i = 0; i <= n; ++i) {
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
        int flow = INF;
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
Flow<305> f;
int n, k, d;
int st, ed;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> d;
    f.init(n + d + 2);
    st = n + d;
    ed = st + 1;
    for(int i = 0; i < d; ++i) {
        int a;
        cin >> a;
        f.addEdge(n + i, ed, a);
    }
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int a;
            cin >> a;
            a--;
            f.addEdge(i, n + a, 1);
        }
        f.addEdge(st, i, k);
    }

    int res = f.maxFlow(st, ed);
    cout << res;

    return 0;
}
