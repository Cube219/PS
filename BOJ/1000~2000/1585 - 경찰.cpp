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
class MCMF
{
public:
    struct Edge
    {
        int dst;
        int c;
        int f;
        int cost;
        int revIdx;
    };

    vector<Edge> g[N + 1];
    int pre[N + 1];
    Edge* path[N + 1];
    bool inQ[N + 1];
    int dis[N + 1];
    int n;

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
    }

    void addEdge(int s, int e, int c, int cost, bool biDir = false)
    {
        Edge e1 = { e, c, 0, cost, -1 };
        Edge e2 = { s, 0, 0, -cost, -1 };
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

    pair<int, int> flow(int st, int ed)
    {
        for(int i = 0; i <= n; ++i) {
            pre[i] = -1;
            inQ[i] = false;
            dis[i] = INF;
        }
        queue<int> q;
        q.push(st);
        inQ[st] = true;
        dis[st] = 0;
        while(q.empty() == false) {
            int cur = q.front();
            q.pop();
            inQ[cur] = false;
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int c = nx.c;
                int f = nx.f;
                int cost = nx.cost;
                if(c > f && dis[nxt] > dis[cur] + cost) {
                    dis[nxt] = dis[cur] + cost;
                    pre[nxt] = cur;
                    path[nxt] = &nx;
                    if(inQ[nxt] == false) {
                        q.push(nxt);
                        inQ[nxt] = true;
                    }
                }
            }
        }
        if(pre[ed] == -1) return { 0, 0 };
        int flow = INF;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        int cost = 0;
        while(idx != st) {
            addFlow(*path[idx], flow);
            cost += path[idx]->cost * flow;
            idx = pre[idx];
        }
        return { flow, cost };
    }

    pair<int, int> mcmf(int st, int ed)
    {
        pair<int, int> res = { 0, 0 };
        while(1) {
            pair<int, int> f = flow(st, ed);
            if(f.first == 0) break;
            res.first += f.first;
            res.second += f.second;
        }

        return res;
    }
};
MCMF<105> mn, mx;
int n, t, f;
int sTime[51], eTime[51];
bool isPos = true;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> sTime[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> eTime[i];
    }
    cin >> t >> f;
    int st = n * 2;
    int ed = n * 2 + 1;
    mn.init(n * 2 + 2);
    mx.init(n * 2 + 2);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(sTime[i] >= eTime[j]) continue;
            int dt = eTime[j] - sTime[i];
            dt = t - dt;
            if(dt < 0) dt = 0;
            int cost = min(f, dt * dt);
            mn.addEdge(i, n + j, 1, cost);
            mx.addEdge(i, n + j, 1, -cost);
        }
    }
    for(int i = 0; i < n; ++i) {
        mn.addEdge(st, i, 1, 0);
        mx.addEdge(st, i, 1, 0);
        mn.addEdge(n + i, ed, 1, 0);
        mx.addEdge(n + i, ed, 1, 0);
    }

    int mnRes = 0, mxRes = 0;
    for(int i = 0; i < n; ++i) {
        auto r1 = mn.flow(st, ed);
        auto r2 = mx.flow(st, ed);
        if(r1.first == 0) {
            isPos = false;
            break;
        }
        mnRes += r1.second;
        mxRes -= r2.second;
    }
    if(isPos == false) {
        cout << "-1";
    } else {
        cout << mnRes << " " << mxRes;
    }

    return 0;
}
