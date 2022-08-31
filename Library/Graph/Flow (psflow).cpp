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
    Flow(int n) : g(n), level(n), idx(n) {}
    void addEdge(int u, int v, int c, bool biDir = false)
    {
        Nxt uu = { v, -1, c, 0 };
        Nxt vv = { u, -1, 0, 0 };
        if(biDir) vv.c = c;
        uu.revIdx = g[v].size(); vv.revIdx = g[u].size();
        g[u].push_back(uu); g[v].push_back(vv);
    }
    void addFlow(Nxt& e, T f)
    {
        e.f += f;
        g[e.nxt][e.revIdx].f -= f;
    }

    bool initLevel(int st, int ed)
    {
        fill(level.begin(), level.end(), -1);
        level[st] = 0;
        queue<int> q;
        q.push(st);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(auto [nxt, _, c, f] : g[cur]) {
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        return level[ed] != -1;
    }

    T flow(int cur, int ed, T minFlow)
    {
        if(cur == ed) return minFlow;
        for(int& i = idx[cur]; i < g[cur].size(); ++i) {
            auto [nxt, _, c, f] = g[cur][i];
            if(level[nxt] == level[cur] + 1 && c > f) {
                T res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
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
        while(initLevel(st, ed)) {
            fill(idx.begin(), idx.end(), 0);
            T f = flow(st, ed, T_INF);
            if(f == 0) break;
            res += f;
        }
        return res;
    }
};
