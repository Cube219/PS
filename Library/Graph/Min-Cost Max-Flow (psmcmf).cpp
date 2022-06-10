struct MCMF
{
    using Type = ll;
    constexpr Type TINF = LNF;

    struct Edge
    {
        int dst;
        Type c;
        Type f;
        Type cost;
        int revIdx;
    };

    vector<vector<Edge>> g;
    vector<int> pre;
    vector<Edge*> path;
    vector<char> inQ;
    vector<Type> dis;
    int n;

    MCMF(int _n)
    {
        n = _n;
        g.resize(n);
        pre.resize(n);
        path.resize(n);
        inQ.resize(n);
        dis.resize(n);
    }

    void addEdge(int s, int e, Type c, Type cost)
    {
        Edge e1 = { e, c, 0, cost, -1 };
        Edge e2 = { s, 0, 0, -cost, -1 };
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

    pair<Type, Type> flow(int st, int ed)
    {
        for(int i = 0; i < n; ++i) {
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
                Type c = nx.c;
                Type f = nx.f;
                Type cost = nx.cost;
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
        Type flow = TINF;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        Type cost = 0;
        while(idx != st) {
            addFlow(*path[idx], flow);
            cost += path[idx]->cost * flow;
            idx = pre[idx];
        }
        return { flow, cost };
    }

    pair<Type, Type> mcmf(int st, int ed)
    {
        pair<Type, Type> res = { 0, 0 };
        while(1) {
            pair<Type, Type> f = flow(st, ed);
            if(f.first == 0) break;
            res.first += f.first;
            res.second += f.second;
        }

        return res;
    }
};
