#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

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

    vector<vector<Edge>> g;
    int n;
    vector<int> level, work;

    Flow(int _n)
    {
        n = _n;
        g.resize(n);
        level.resize(n);
        work.resize(n);
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

    bool initLevel(int st, int ed)
    {
        for(int i = 0; i < n; ++i) {
            level[i] = -1;
        }
        level[st] = 0;
        queue<int> q;
        q.push(st);
        while(q.empty() == false) {
            int cur = q.front();
            q.pop();
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int c = nx.c;
                int f = nx.f;
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        if(level[ed] == -1) return false;
        return true;
    }

    int flow(int cur, int ed, int minFlow)
    {
        if(cur == ed) return minFlow;

        for(int i = work[cur]; i < g[cur].size(); ++i) {
            auto& nx = g[cur][i];
            int nxt = nx.dst;
            int c = nx.c;
            int f = nx.f;
            if(level[nxt] == level[cur] + 1 && c > f) {
                int res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
                    addFlow(nx, res);
                    return res;
                }
            }
            work[cur]++;
        }
        return 0;
    }

    int maxFlow(int st, int ed)
    {
        int res = 0;
        while(1) {
            if(initLevel(st, ed) == false) break;
            for(int i = 0; i < n; ++i) {
                work[i] = 0;
            }
            while(1) {
                int f = flow(st, ed, INF);
                if(f == 0) break;
                res += f;
            }
        }

        return res;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    for(auto& v : p) cin >> v;
    struct Node
    {
        int a, b, c;
    };
    vector<Node> d(m);
    for(auto& v : d) {
        cin >> v.a >> v.b >> v.c;
        v.a--; v.b--;
    }

    Flow f(n + m + 2);
    int st = n + m;
    int ed = st + 1;

    for(int i = 0; i < n; ++i) {
        f.addEdge(st, i, p[i]);
    }
    for(int i = 0; i < m; ++i) {
        f.addEdge(n + i, ed, d[i].c);
        f.addEdge(d[i].a, n + i, INF);
        f.addEdge(d[i].b, n + i, INF);
    }

    int res = 0;
    for(auto& v : d) res += v.c;
    int r2 = f.maxFlow(st, ed);
    cout << res - r2;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
