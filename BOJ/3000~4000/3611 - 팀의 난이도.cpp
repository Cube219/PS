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
        double c;
        double f;
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

    void addEdge(int s, int e, double c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void clear()
    {
        for(auto& cur : g) {
            for(auto& eg : cur) {
                eg.f = 0;
            }
        }
    }

    void addFlow(Edge& e, double f)
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
                double c = nx.c;
                double f = nx.f;
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        if(level[ed] == -1) return false;
        return true;
    }

    double flow(int cur, int ed, double minFlow)
    {
        if(cur == ed) return minFlow;

        for(int i = work[cur]; i < g[cur].size(); ++i) {
            auto& nx = g[cur][i];
            int nxt = nx.dst;
            double c = nx.c;
            double f = nx.f;
            if(level[nxt] == level[cur] + 1 && c > f) {
                double res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
                    addFlow(nx, res);
                    return res;
                }
            }
            work[cur]++;
        }
        return 0;
    }

    double maxFlow(int st, int ed)
    {
        double res = 0;
        while(1) {
            if(initLevel(st, ed) == false) break;
            for(int i = 0; i < n; ++i) {
                work[i] = 0;
            }
            while(1) {
                double f = flow(st, ed, INF);
                if(abs(f) < 1e-8) break;
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
    struct Node
    {
        int a, b;
    };
    vector<Node> d(m);
    for(auto& v : d) {
        cin >> v.a >> v.b;
        v.a--; v.b--;
    }

    Flow f(n + m + 2);
    int st = n + m;
    int ed = st + 1;

    for(int i = 0; i < m; ++i) {
        f.addEdge(n + i, ed, 1);
        f.addEdge(d[i].a, n + i, INF);
        f.addEdge(d[i].b, n + i, INF);
    }

    vector<int> res;
    double lo = 0, hi = m;
    while((hi - lo) > 1e-8) {
        double mid = (lo + hi) / 2;
        for(int i = 0; i < n; ++i) {
            f.addEdge(st, i, mid);
        }
        f.clear();
        double cut = f.maxFlow(st, ed);

        vector<int> tmp;
        for(int i = 0; i < n; ++i) {
            if(f.initLevel(st, i) == false) {
                tmp.push_back(i);
            }
        }
        for(int i = n - 1; i >= 0; --i) {
            auto& eg = f.g[st].back();
            f.g[eg.dst].pop_back();
            f.g[st].pop_back();
        }

        if(tmp.size() == 0 || m - cut <= 0) {
            hi = mid;
        } else {
            lo = mid;
            res = tmp;
        }
    }
    sort(res.begin(), res.end());
    if(res.size() == 0) res.push_back(0);

    cout << res.size() << "\n";
    for(int v : res) cout << v + 1 << "\n";
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
