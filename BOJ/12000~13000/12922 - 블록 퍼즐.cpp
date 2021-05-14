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

int n;
char map[55][55];
int dstx, dsty;
int dx[] = { 0, 3, 0, -3 };
int dy[] = { 3, 0, -3, 0 };
int num[55][55];
Flow<6000> f;
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(map[i][j] == '$') {
                dstx = i;
                dsty = j;
                break;
            }
        }
    }

    queue<pair<int, int>> q;
    q.push({ dstx, dsty });

    int nodenum = 0;
    num[dstx][dsty] = ++nodenum;

    while(q.empty() == false) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(num[nx][ny] != 0 || map[nx][ny] == 'H') continue;

            num[nx][ny] = ++nodenum;
            q.push({ nx, ny });
        }
    }

    f.init(n * n);

    int st = ++nodenum;
    int ed = st + 1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(num[i][j] > 0) {
                int cnum = num[i][j];
                if(map[i][j] == '.') {
                    f.addEdge(cnum * 2, cnum * 2 + 1, 1);
                } else {
                    f.addEdge(cnum * 2, cnum * 2 + 1, INF);
                }
                for(int k = 0; k < 4; ++k) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    int nnum = num[nx][ny];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                    if(num[nx][ny] == 0) continue;
                    int cap = 0;
                    bool hasb = false;
                    if(i == nx) {
                        for(int y = j + 1; y <= ny - 1; ++y) {
                            if(map[i][y] == '.') cap++;
                            else if(map[i][y] == 'b') hasb = true;
                        }
                        for(int y = ny + 1; y <= j - 1; ++y) {
                            if(map[i][y] == '.') cap++;
                            else if(map[i][y] == 'b') hasb = true;
                        }
                    } else {
                        for(int x = i + 1; x <= nx - 1; ++x) {
                            if(map[x][j] == '.') cap++;
                            else if(map[x][j] == 'b') hasb = true;
                        }
                        for(int x = nx + 1; x <= i - 1; ++x) {
                            if(map[x][j] == '.') cap++;
                            else if(map[x][j] == 'b') hasb = true;
                        }
                    }
                    if(hasb == true) cap = INF;
                    if(cap > 0) {
                        f.addEdge(cnum * 2 + 1, nnum * 2, cap);
                        // f.addEdge(nnum * 2 + 1, cnum * 2, cap);
                    }
                }

                if(map[i][j] == '$') {
                    f.addEdge(cnum * 2 + 1, ed * 2, INF);
                } else if(map[i][j] == 'b') {
                    f.addEdge(st * 2, cnum * 2, INF);
                }
            }
        }
    }

    res = f.maxFlow(st * 2, ed * 2);
    if(res >= (ll)INF - 10) res = -1;
    cout << res;

    return 0;
}
