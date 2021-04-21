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

Flow<10000> f;
int n, q, s;
int qsize[31], wsize[31], dstq[101];
int sum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q >> s;
    int stq = s;
    int stw = stq + q * n * 2;
    int st = stw + n * 2;
    int ed = st + 1;
    f.init(ed + 1);

    for(int i = 0; i < s; ++i) {
        cin >> dstq[i];
        dstq[i]--;
        f.addEdge(st, i, INF);
    }
    for(int i = 0; i < q; ++i) {
        cin >> qsize[i];
        for(int j = 0; j < n; ++j) {
            int t = stq + j * (q * 2) + i * 2;
            f.addEdge(t, t + 1, qsize[i]);
            if(j > 0) {
                f.addEdge(t - q * 2 + 1, t, INF);
            }
            f.addEdge(t + 1, stw + j * 2, INF);
        }
    }
    for(int i = 0; i < n; ++i) {
        int cap;
        cin >> cap;
        f.addEdge(stw + i * 2, stw + i * 2 + 1, cap);
        f.addEdge(stw + i * 2 + 1, ed, INF);
        for(int j = 0; j < s; ++j) {
            int a;
            cin >> a;
            int curstq = stq + i * q * 2;
            f.addEdge(i, curstq + dstq[j] * 2, a);
            sum += a;
        }
    }

    int res = f.maxFlow(st, ed);
    if(sum > res) cout << "impossible";
    else cout << "possible";

    return 0;
}
