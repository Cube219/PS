#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#include <iomanip>
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
    int n;
    int level[N + 1];
    int work[N + 1];

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

int tNum;
int n, m, st, ed;
Flow<1005> f;
vector<pair<int, int>> g[1001];

bool comp[1001];
int d[1001];
int dijk()
{
    for(int i = 0; i < n; ++i) {
        d[i] = 0;
        comp[i] = false;
    }
    priority_queue<pair<int, int>> pq;
    pq.push({ INF, st });
    d[st] = INF;
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(comp[cur] == true) continue;

        comp[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            int cost = min(nx.second, d[cur]);
            if(d[nxt] < cost) {
                d[nxt] = cost;
                pq.push({ d[nxt], nxt });
            }
        }
    }
    return d[ed];
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
        cin >> n >> m >> st >> ed;
        f.init(n + 2);
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for(int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            f.addEdge(a, b, c);
            g[a].push_back({ b, c });
        }
        int a = f.maxFlow(st, ed);
        int b = dijk();

        cout << fixed << setprecision(3) << (double)a / b << "\n";
    }

    return 0;
}
