struct MCMF
{
    using T = ll;
    const T T_INF = LNF;
    struct Nxt
    {
        int nxt, revIdx;
        T c, f, cost;
    };
    vector<vector<Nxt>> g;
    vector<int> pre;
    vector<T> dis;
    vector<Nxt*> eg;
    vector<char> inQ;
    MCMF(int n) : g(n), pre(n), dis(n), eg(n), inQ(n) {}
    void addEdge(int u, int v, T c, T cost)
    {
        Nxt uu = { v, -1, c, 0, cost };
        Nxt vv = { u, -1, 0, 0, -cost };
        uu.revIdx = g[v].size(); vv.revIdx = g[u].size();
        g[u].push_back(uu); g[v].push_back(vv);
    }
    void addFlow(Nxt& e, T f)
    {
        e.f += f;
        g[e.nxt][e.revIdx].f -= f;
    }

    pair<T, T> flow(int st, int ed)
    {
        fill(pre.begin(), pre.end(), -1);
        fill(dis.begin(), dis.end(), T_INF);
        fill(inQ.begin(), inQ.end(), true);
        queue<int> q;
        q.push(st); inQ[st] = true;
        dis[st] = 0;
        while(!q.empty()) {
            int cur = q.front(); q.pop(); inQ[cur] = false;
            for(auto& nx : g[cur]) {
                auto [nxt, _, c, f, cost] = nx;
                if(c > f && dis[nxt] > dis[cur] + cost) {
                    dis[nxt] = dis[cur] + cost;
                    pre[nxt] = cur;
                    eg[nxt] = &nx;
                    if(!inQ[nxt]) {
                        q.push(nxt); inQ[nxt] = true;
                    }
                }
            }
        }
        if(pre[ed] == -1) return { 0, 0 };
        T minF = T_INF;
        for(int i = ed; i != st; i = pre[i]) minF = min(minF, eg[i]->c - eg[i]->f);
        T cost = 0;
        for(int i = ed; i != st; i = pre[i]) {
            addFlow(*eg[i], minF);
            cost += minF * eg[i]->cost;
        }
        return { minF, cost };
    }

    pair<T, T> maxFlow(int st, int ed)
    {
        pair<T, T> res = { 0, 0 };
        while(1) {
            auto f = flow(st, ed);
            if(f.first == 0) break;
            res.first += f.first;
            res.second += f.second;
        }
        return res;
    }
};
