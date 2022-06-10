vector<int> a(n, -1), b(m, -1);
for(int i = 0; i < n; ++i) {
    if(a[i] != -1) continue;
    vector<char> isComp(n, false);

    auto dfs = [&](auto&& self, int cur) -> bool {
        isComp[cur] = true;
        for(int nxt : g[cur]) {
            if(b[nxt] == -1) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            } else if(isComp[b[nxt]] == false) {
                bool f = self(self, b[nxt]);
                if(f == true) {
                    a[cur] = nxt;
                    b[nxt] = cur;
                    return true;
                }
            }
        }
        return false;
    };
    dfs(dfs, i);
}
