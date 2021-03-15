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
Flow<201> f;

int tNum;
int n;
int d[101];
char str[201][201];
bool isadj[101];
constexpr int INF = 987654321;

bool isPos(int k)
{
    f.init(n * 2 + 2);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i == j || str[i][j] == 'Y') {
                if(d[j] == 0) {
                    isadj[i] = true;
                } else {
                    f.addEdge(i, n + j, INF);
                }
            }
        }
    }

    int st = n * 2;
    int ed = st + 1;

    for(int i = 0; i < n; ++i) {
        if(d[i] != 0) {
            f.addEdge(st, i, d[i]);
            if(isadj[i] == true) {
                f.addEdge(n + i, ed, k);
            } else {
                f.addEdge(n + i, ed, 1);
            }
        }
    }

    f.maxFlow(st, ed);

    int res = INF;
    for(int i = 0; i < n; ++i) {
        if(isadj[i] == true) {
            for(int j = 0; j < f.g[n + i].size(); ++j) {
                int ff = f.g[n + i][j].f;
                if(ff <= 0) continue;
                res = min(res, ff);
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < f.g[n + i].size(); ++j) {
            auto& e = f.g[n + i][j];
            if(e.dst == ed) {
                if(e.f != e.c) return false;
            }
        }
    }
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        f.init(n * 2 + 2);

        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            isadj[i] = false;
        }
        for(int i = 0; i < n; ++i) {
            cin >> str[i];
        }

        int l = 1;
        int r = 10000;
        while(l + 1 < r) {
            int m = (l + r) / 2;
            if(isPos(m) == true) {
                l = m;
            } else {
                r = m;
            }
        }
        cout << l << "\n";
    }

    return 0;
}
