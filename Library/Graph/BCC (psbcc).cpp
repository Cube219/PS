vector<vector<pair<int, int>>> bcc;
vector<int> dep(n, 0), isCut(n, false);
vector<pair<int, int>> st;
int dNum;
auto dfs = [&](auto&& self, int cur, int pre) -> int {
    dep[cur] = ++dNum;

    int ret = dep[cur];
    int cNum = 0;
    for(int nxt : g[cur]) {
        if(nxt == pre) continue;

        if(dep[nxt] == 0 || dep[cur] > dep[nxt]) {
            st.push_back({ cur, nxt });
        }

        if(dep[nxt] == 0) {
            cNum++;
            int t = self(self, nxt, cur);
            if(t >= dep[cur]) {
                if(dep[cur] != 1) isCut[cur] = true;

                bcc.push_back({});
                vector<pair<int, int>>& cbcc = bcc.back();
                while(1) {
                    auto top = st.back();
                    st.pop_back();

                    cbcc.push_back(top);
                    if(top.first == cur) break;
                }
            }
            ret = min(ret, t);
        } else ret = min(ret, dep[nxt]);
    }

    if(dep[cur] == 1 && cNum > 1) isCut[cur] = true;

    return ret;
};
for(int i = 0; i < n; ++i) {
    if(dep[i] == 0) {
        dNum = 0;
        dfs(dfs, i, -1);
    }
}
// bridges: bcc[i].size() == 1
