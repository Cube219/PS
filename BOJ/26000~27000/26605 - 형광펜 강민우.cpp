#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct Flow
{
    using T = int;
    const T T_INF = INF;

    struct Nxt
    {
        int nxt, revIdx;
        T c, f;
    };
    vector<vector<Nxt>> g;
    vector<int> level, idx;
    Flow(int n) : g(n), level(n), idx(n)
    {
    }
    void addEdge(int u, int v, int c, bool biDir = false)
    {
        Nxt uu = {v, -1, c, 0};
        Nxt vv = {u, -1, 0, 0};
        if (biDir) vv.c = c;
        uu.revIdx = g[v].size();
        vv.revIdx = g[u].size();
        g[u].push_back(uu);
        g[v].push_back(vv);
    }
    void addFlow(Nxt& e, T f)
    {
        e.f += f;
        g[e.nxt][e.revIdx].f -= f;
    }

    void clear()
    {
        for (auto& v : g)
            for (auto& v2 : v) v2.f = 0;
    }

    bool initLevel(int st, int ed)
    {
        fill(level.begin(), level.end(), -1);
        level[st] = 0;
        queue<int> q;
        q.push(st);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto [nxt, _, c, f] : g[cur]) {
                if (level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        return level[ed] != -1;
    }

    T flow(int cur, int ed, T minFlow)
    {
        if (cur == ed) return minFlow;
        for (int& i = idx[cur]; i < g[cur].size(); ++i) {
            auto [nxt, _, c, f] = g[cur][i];
            if (level[nxt] == level[cur] + 1 && c > f) {
                T res = flow(nxt, ed, min(minFlow, c - f));
                if (res > 0) {
                    addFlow(g[cur][i], res);
                    return res;
                }
            }
        }
        return 0;
    }

    T maxFlow(int st, int ed)
    {
        T res = 0;
        while (initLevel(st, ed)) {
            fill(idx.begin(), idx.end(), 0);
            T f = flow(st, ed, T_INF);
            if (f == 0) break;
            res += f;
        }
        return res;
    }
};

void solve()
{
    int n, m, a, b, k;
    cin >> n >> m >> a >> b >> k;
    a--;
    b--;
    k--;
    Flow f(n);

    struct Edge
    {
        int u, v;
    };
    vector<Edge> eg;
    struct Edge2
    {
        int u, uIdx;
        int v, vIdx;
        int c;
    };
    vector<Edge2> rmEdges;

    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;

        u--;
        v--;
        eg.push_back({u, v});
        f.addEdge(u, v, c, true);

        if (u == k || v == k) {
            rmEdges.push_back(
                {u, (int)f.g[u].size() - 1, v, (int)f.g[v].size() - 1, c});
        }
    }

    f.initLevel(a, b);

    int res = f.maxFlow(a, b);
    cout << res << "\n";

    bool bHasRes = false;
    for (auto [u, uIdx, v, vIdx, c] : rmEdges) {
        f.clear();
        f.g[u][uIdx].c = 0;
        f.g[v][vIdx].c = 0;

        f.initLevel(a, b);
        int curRes = f.maxFlow(a, b);

        if (curRes + c == res) {
            vector<char> reach(n, false);
            reach[a] = true;
            queue<int> q;
            q.push(a);
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                for (auto& nx : f.g[cur]) {
                    if (nx.c > nx.f && !reach[nx.nxt]) {
                        reach[nx.nxt] = true;
                        q.push(nx.nxt);
                    }
                }
            }

            vector<Edge> resEg;
            for (auto [u, v] : eg) {
                if (reach[u] != reach[v]) {
                    resEg.push_back({u, v});
                }
            }

            cout << resEg.size() << "\n";
            for (auto [u, v] : resEg) cout << u + 1 << " " << v + 1 << "\n";

            bHasRes = true;
            break;
        }

        f.g[u][uIdx].c = c;
        f.g[v][vIdx].c = c;
    }

    if (!bHasRes) cout << "-1";
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
