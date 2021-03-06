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

int n, f, d;
Flow<501> fl;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> f >> d;
    fl.init(f + d + n * 2 + 5);
    int fst = n * 2;
    int dst = fst + f;
    for(int i = 0; i < n; ++i) {
        int fs, ds;
        cin >> fs >> ds;
        int ff, dd;
        for(int j = 0; j < fs; ++j) {
            cin >> ff;
            ff--;
            fl.addEdge(fst + ff, i * 2, 1);
        }
        for(int j = 0; j < ds; ++j) {
            cin >> dd;
            dd--;
            fl.addEdge(i * 2 + 1, dst + dd, 1);
        }
        fl.addEdge(i * 2, i * 2 + 1, 1);
    }
    int st = dst  + d;
    int ed = st + 1;
    for(int i = 0; i < f; ++i) {
        fl.addEdge(st, fst + i, 1);
    }
    for(int i = 0; i < d; ++i) {
        fl.addEdge(dst + i, ed, 1);
    }

    cout << fl.maxFlow(st, ed);

    return 0;
}
