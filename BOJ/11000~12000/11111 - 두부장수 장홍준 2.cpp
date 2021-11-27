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

    void addEdge(int s, int e, int c, int cost)
    {
        Edge e1 = { e, c, 0, cost, -1 };
        Edge e2 = { s, 0, 0, -cost, -1 };
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

vector<vector<int>> cost;
int n, m;
vector<vector<int>> g;
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
MCMF<5005> mf;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cost.resize(5);
    cost[0] = { 10, 8, 7, 5, 1 };
    cost[1] = { 8, 6, 4, 3, 1 };
    cost[2] = { 7, 4, 3, 2, 1 };
    cost[3] = { 5, 3, 2, 2, 1 };
    cost[4] = { 1, 1, 1, 1, 0 };

    int n, m;
    cin >> n >> m;
    g.resize(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j) {
            g[i][j] = str[j] - 'A';
            if(str[j] == 'F') g[i][j]--;
        }
    }

    mf.init(n * m + 2);
    int st = n * m;
    int ed = st + 1;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int cur = i * m + j;
            if((i + j) % 2 == 1) {
                mf.addEdge(cur, ed, 1, 0);
                continue;
            }
            mf.addEdge(cur, ed, 1, 0);
            mf.addEdge(st, cur, 1, 0);
            for(int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

                int nxt = nx * m + ny;
                mf.addEdge(cur, nxt, 1, -cost[g[i][j]][g[nx][ny]]);
            }
        }
    }

    auto res = mf.mcmf(st, ed);
    cout << -res.second;

    return 0;
}
