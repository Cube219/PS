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

struct Flow
{
    using Type = int;

    struct Edge
    {
        int dst;
        Type c;
        Type f;
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

    void addEdge(int s, int e, Type c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void addFlow(Edge& e, Type f)
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
                Type c = nx.c;
                Type f = nx.f;
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        if(level[ed] == -1) return false;
        return true;
    }

    Type flow(int cur, int ed, Type minFlow)
    {
        if(cur == ed) return minFlow;

        for(int i = work[cur]; i < g[cur].size(); ++i) {
            auto& nx = g[cur][i];
            int nxt = nx.dst;
            Type c = nx.c;
            Type f = nx.f;
            if(level[nxt] == level[cur] + 1 && c > f) {
                Type res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
                    addFlow(nx, res);
                    return res;
                }
            }
            work[cur]++;
        }
        return 0;
    }

    Type maxFlow(int st, int ed)
    {
        Type res = 0;
        while(1) {
            if(initLevel(st, ed) == false) break;
            for(int i = 0; i < n; ++i) {
                work[i] = 0;
            }
            while(1) {
                Type f = flow(st, ed, INF);
                if(f == 0) break;
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
    vector<vector<int>> g(n);
    struct Edge
    {
        int u, v;
    };
    vector<Edge> eg(m);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);

        eg[i] = { u, v };
    }
    vector<int> d(n);
    for(auto& v : d) cin >> v;
    int q;
    cin >> q;
    struct QNode
    {
        int t, u, i, v, j;
    };
    vector<QNode> qList(q);
    for(auto& v : qList) cin >> v.t >> v.u >> v.i >> v.v >> v.j;

    vector<vector<int>> bit(n, vector<int>(16, -1));
    for(int i = 0; i < n; ++i) {
        if(d[i] == -1) continue;

        for(int j = 0; j < 16; ++j) {
            bit[i][j] = (d[i] & (1 << j)) ? 1 : 0;
        }
    }

    ll res = LNF;

    auto cal = [&]() {
        ll v = 0;
        for(int b = 0; b < 16; ++b) {
            int num = 0;

            Flow f(n + 2);
            int zero = n;
            int one = n + 1;

            for(auto [u, v] : eg) {
                if(bit[u][b] != -1 && bit[v][b] != -1) {
                    num += bit[u][b] ^ bit[v][b];
                } else if(bit[u][b] != -1) {
                    if(bit[u][b] == 0) {
                        f.addEdge(zero, v, 1);
                    } else {
                        f.addEdge(v, one, 1);
                    }
                } else if(bit[v][b] != -1) {
                    if(bit[v][b] == 0) {
                        f.addEdge(zero, u, 1);
                    } else {
                        f.addEdge(u, one, 1);
                    }
                } else {
                    f.addEdge(u, v, 1, true);
                }
            }
            num += f.maxFlow(zero, one);

            v += num;
        }
        res = min(res, v);
    };

    auto bt = [&](auto&& self, int idx) -> void {
        if(idx == q) {
            cal();
            return;
        }

        auto& c = qList[idx];
        auto& uBit = bit[c.u][c.i];
        auto& vBit = bit[c.v][c.j];

        auto oldU = uBit;
        auto oldV = vBit;
        if(uBit == -1 && vBit == -1) {
            // u를 0
            uBit = 0;
            vBit = c.t ? 1 : 0;
            self(self, idx + 1);

            // u를 1
            uBit = 1;
            vBit = c.t ? 0 : 1;
            self(self, idx + 1);
        } else {
            if(uBit == -1) {
                uBit = c.t ? 1 - vBit : vBit;
                self(self, idx + 1);
            } else if(vBit == -1) {
                vBit = c.t ? 1 - uBit : uBit;
                self(self, idx + 1);
            } else {
                if(c.t == 0 && uBit == vBit) self(self, idx + 1);
                else if(c.t == 1 && uBit != vBit) self(self, idx + 1);
            }
        }

        uBit = oldU;
        vBit = oldV;
    };
    bt(bt, 0);

    if(res == LNF) res = -1;
    cout << res;
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
