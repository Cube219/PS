vector<vector<pair<int, int>>> bccs;
vector<int> dep(n, -1); int dNum;
vector<char> isCut(n, false);
vector<pair<int, int>> st;
auto bcc_dfs = [&](auto&& self, int cur, int pre) -> int {
    dep[cur] = dNum++;
    int ret = dep[cur];
    int cNum = 0;

    for(int nxt : g[cur]) {
        if(nxt == pre) continue;

        if(dep[nxt] == -1 || dep[nxt] < dep[cur]) st.push_back({ cur, nxt });
        if(dep[nxt] == -1) {
            cNum++;
            int t = self(self, nxt, cur);
            if(t >= dep[cur]) {
                if(dep[cur] > 0) isCut[cur] = true;

                bccs.push_back({});
                auto& bcc = bccs.back();
                while(1) {
                    auto eg = st.back(); st.pop_back();
                    bcc.push_back(eg);

                    if(eg.first == cur) break;
                }
            }
            ret = min(ret, t);
        } else ret = min(ret, dep[nxt]);
    }

    if(dep[cur] == 0 && cNum > 1) isCut[cur] = true;
    return ret;
};

for(int i = 0; i < n; ++i) {
    if(dep[i] == -1) {
        dNum = 0;
        bcc_dfs(bcc_dfs, i, -1);
    }
}
// bridges: bcc[i].size() == 1
