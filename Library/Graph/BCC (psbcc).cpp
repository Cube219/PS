vector<vector<pair<int, int>>> bcc;
vector<int> d(n, 0), isCut(n, false);
vector<pair<int, int>> st;
int dNum;
auto dfs = [&](auto&& self, int cur, int pre) -> int {
    d[cur] = ++dNum;

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(nxt == pre) continue;

        if(d[nxt] == 0 || d[cur] > d[nxt]) {
            st.push_back({ cur, nxt });
        }

        if(d[nxt] == 0) {
            int t = self(self, nxt, cur);
            if(t >= d[cur]) {
                if(d[cur] != 0 || d[nxt] > 1) isCut[cur] = true;

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
        } else ret = min(ret, d[nxt]);
    }

    return ret;
};
for(int i = 0; i < n; ++i) {
    if(d[i] == 0) {
        dNum = 0;
        dfs(dfs, i, -1);
    }
}
// bridges: bcc[i].size() == 1
