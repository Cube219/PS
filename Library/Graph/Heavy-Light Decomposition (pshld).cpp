vector<int> sz(n), dep(n), par(n);
vector<vector<int>> g2(n);
dep[0] = 0; par[0] = -1;
auto dfs = [&](auto&& self, int cur, int pre) -> int {
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == pre) continue;
        dep[nxt] = dep[cur] + 1;
        par[nxt] = cur;
        sz[cur] += self(self, nxt, cur);

        g2[cur].push_back(nxt);
        if(sz[g2[cur][0]] < sz[nxt]) swap(g2[cur][0], g2[cur].back());
    }
    return sz[cur];
};
dfs(dfs, 0, -1);

vector<int> top(n), idx(n); int num = 0;
top[0] = 0;
auto hld = [&](auto&& self, int cur) -> void {
    idx[cur] = num++;
    bool heavy = true;
    for(int nxt : g2[cur]) {
        top[nxt] = heavy ? top[cur] : nxt;
        self(self, nxt);
        heavy = false;
    }
};
hld(hld, 0);
