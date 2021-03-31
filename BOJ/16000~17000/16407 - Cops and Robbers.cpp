#define _CRT_SECURE_NO_WARNINGS 1

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

    ll flow(int st, int ed)
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
                ll c = nx.c;
                ll f = nx.f;
                if(c > f && pre[nxt] == -1) {
                    pre[nxt] = cur;
                    path[nxt] = &nx;
                    q.push(nxt);
                    if(nxt == ed) break;
                }
            }
        }
        if(pre[ed] == -1) return 0;
        ll flow = INF;
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

    ll maxFlow(int st, int ed)
    {
        ll res = 0;
        while(1) {
            ll f = flow(st, ed);
            if(f == 0) break;
            res += f;
        }

        return res;
    }
};

Flow<3001> f;
int n, m, cNum;
int c[30];
char str[35][35];
int map[35][35];
int st, ed;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
bool isPos = true;
bool visit[35][35];

void ck()
{
    int sx, sy;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(map[i][j] == -1) {
                sx = i;
                sy = j;
                break;
            }
        }
    }
    queue<pair<int, int>> q;
    q.push({ sx, sy });
    while(q.empty() == false) {
        auto pos = q.front();
        q.pop();
        if(map[pos.first][pos.second] == -2) {
            isPos = false;
            break;
        } else if(map[pos.first][pos.second] > 0) continue;
        for(int i = 0; i < 4; ++i) {
            int nx = pos.first + dx[i];
            int ny = pos.second + dy[i];
            if(visit[nx][ny] == true) continue;
            visit[nx][ny] = true;
            q.push({ nx, ny });
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n >> cNum;
    for(int i = 0; i < n; ++i) {
        cin >> str[i];
    }
    for(int i = 1; i <= cNum; ++i) {
        cin >> c[i];
    }

    for(int i = 0; i <= n + 1; ++i) {
        for(int j = 0; j <= m + 1; ++j) {
            map[i][j] = -2;
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(str[i][j] == 'B') {
                map[i + 1][j + 1] = -1;
            } else if(str[i][j] >= 'a' && str[i][j] <= 'z') {
                map[i + 1][j + 1] = (int)(str[i][j] - 'a') + 1;
            } else {
                map[i + 1][j + 1] = 0;
            }
        }
    }
    ck();

    if(isPos == true) {
        st = (n + 2) * (m + 2) * 2 + 1;
        ed = (n + 2) * (m + 2) * 2 + 2;
        f.init((n + 2) * (m + 2) * 2 + 3);

        for(int i = 0; i <= n + 1; ++i) {
            for(int j = 0; j <= m + 1; ++j) {
                int num = i * (m + 2) + j;

                if(map[i][j] == -2) {
                    f.addEdge(num * 2, num * 2 + 1, INF);
                    f.addEdge(num * 2 + 1, ed, INF);
                } else {
                    if(map[i][j] == -1) {
                        f.addEdge(st, num * 2, INF);
                    }
                    ll cost = map[i][j];
                    if(cost == -1 || cost == 0) cost = INF;
                    else  cost = c[cost];
                    f.addEdge(num * 2, num * 2 + 1, cost);

                    for(int k = 0; k < 4; ++k) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        int num2 = nx * (m + 2) + ny;
                        f.addEdge(num * 2 + 1, num2 * 2, INF);
                    }
                }
            }
        }
        ll r = f.maxFlow(st, ed);
        cout << r;
    } else {
        cout << "-1";
    }

    return 0;
}
