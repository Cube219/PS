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
constexpr ll INF = 99999999999999999;

template <int N>
class Flow
{
public:
    struct Edge
    {
        int dst;
        ll c;
        ll f;
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

    void addEdge(int s, int e, ll c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void addFlow(Edge& e, ll f)
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
                ll c = nx.c;
                ll f = nx.f;
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        if(level[ed] == -1) return false;
        return true;
    }

    ll flow(int cur, int ed, ll minFlow)
    {
        if(cur == ed) return minFlow;

        for(int i = work[cur]; i < g[cur].size(); ++i) {
            auto& nx = g[cur][i];
            int nxt = nx.dst;
            ll c = nx.c;
            ll f = nx.f;
            if(level[nxt] == level[cur] + 1 && c > f) {
                ll res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
                    addFlow(nx, res);
                    return res;
                }
            }
            work[cur]++;
        }
        return 0;
    }

    ll maxFlow(int st, int ed)
    {
        ll res = 0;
        while(1) {
            if(initLevel(st, ed) == false) break;
            for(int i = 0; i < n; ++i) {
                work[i] = 0;
            }
            while(1) {
                ll f = flow(st, ed, INF);
                if(f == 0) break;
                res += f;
            }
        }

        return res;
    }
};

int n, m;
Flow<210> flow;
bool visit[210];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    int st = n, ed = st + 1;
    flow.init(ed + 1);

    for(int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if(t <= 0) flow.addEdge(i, ed, -t);
        else flow.addEdge(st, i, t);
    }
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        flow.addEdge(u, v, INF);
    }

    flow.maxFlow(st, ed);
    queue<int> q;
    q.push(st);
    visit[st] = true;
    vector<int> res;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        for(auto& eg : flow.g[cur]) {
            int nxt = eg.dst;
            if(visit[nxt] == true || eg.c <= eg.f) continue;
            res.push_back(nxt);
            visit[nxt] = true;
            q.push(nxt);
        }
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i] + 1 << " ";
    }

    return 0;
}
