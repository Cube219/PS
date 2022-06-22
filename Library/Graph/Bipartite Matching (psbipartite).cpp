vector<int> a(n, -1), b(m, -1), level(n);
auto initLevel = [&]() {
    queue<int> q;
    for(int i = 0; i < n; ++i) {
        if(a[i] == -1) {
            q.push(i);
            level[i] = 0;
        } else level[i] = -1;
    }
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int nxt : g[cur]) {
            if(b[nxt] != -1 && level[b[nxt]] == -1) {
                level[b[nxt]] = level[cur] + 1;
                q.push(b[nxt]);
            }
        }
    }
};
auto dfs = [&](auto&& self, int cur) -> bool {
    for(int nxt : g[cur]) {
        if(b[nxt] == -1 || (level[b[nxt]] == level[cur] + 1 && self(self, b[nxt]))) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        }
    }
    return false;
};
int flow = 0;
while(1) {
    initLevel();
    int f = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] == -1 && dfs(dfs, i)) f++;
    }
    if(f == 0) break;
    flow += f;
}
