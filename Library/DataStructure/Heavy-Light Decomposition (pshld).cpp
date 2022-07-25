vector<int> dep(n), sz(n), top(n), par(n), idx(n);
vector<vector<int>> g2(n);
int num = 0;

dep[0] = 0; sz[0] = 0;
auto dfs = [&](auto&& self, int cur, int p) -> void {
    for(int nxt : g[cur]) {
        if(nxt == p) continue;

        dep[nxt] = dep[cur] + 1;
        par[nxt] = cur;
        g2[cur].push_back(nxt);

        self(self, nxt, cur);
    }
};
dfs(dfs, 0, -1);
auto dfs2 = [&](auto&& self, int cur) -> int {
    sz[cur] = 1;
    for(int& nxt : g2[cur]) {
        sz[cur] += self(self, nxt);

        if(sz[g2[cur][0]] < sz[nxt]) swap(g2[cur][0], nxt);
    }
    return sz[cur];
};
dfs2(dfs2, 0);

// sg.init(n);
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
// sg.build();
