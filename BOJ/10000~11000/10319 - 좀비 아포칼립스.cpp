#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int tNum;
int n, m, r;
int st, num, s;
int ed;
vector<int> h;
bool ish[1001];

constexpr int INF = 987654321;

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
            if(res > num) break;
        }

        return res;
    }
};
Flow<105001> f;

void init()
{
    for(int i = 0; i < n; ++i) {
        ish[i] = false;
    }
    for(int i = 0; i < h.size(); ++i) {
        ish[h[i]] = true;
    }
    f.init(n * (s + 1) + 1);
    h.clear();
    ed = n * (s + 1);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < s; ++j) {
            f.addEdge(i * (s + 1) + j, i * (s + 1) + j + 1, INF);
            if(ish[i] == true) {
                f.addEdge(i * (s + 1) + j, ed, INF);
            }
        }
        if(ish[i] == true) {
            f.addEdge(i * (s + 1) + s, ed, INF);
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        cin >> st >> num >> s;
        st--;
        cin >> m;
        for(int i = 0; i < m; ++i) {
            int a;
            cin >> a;
            a--;
            h.push_back(a);
        }
        init();
        cin >> r;
        for(int i = 0; i < r; ++i) {
            int a, b, p, t;
            cin >> a >> b >> p >> t;
            a--; b--;
            for(int j = s; j >= t; --j) {
                f.addEdge(a * (s + 1) + j - t, b * (s + 1) + j, p);
            }
        }
        int res = f.maxFlow(st * (s + 1), ed);
        cout << min(res, num) << "\n";
    }

    return 0;
}
