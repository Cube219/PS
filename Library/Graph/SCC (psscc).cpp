vector<int> d(n, 0), st(n), finish(n, false), sccIdx(n);
vector<vector<int>> sccs;
int dNum = 0;

auto scc_dfs = [&](auto&& self, int cur) -> int {
    d[cur] = ++dNum;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, self(self, nxt));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur]) {
        sccs.push_back({});
        auto& scc = sccs.back();
        while(1) {
            int top = st.back();
            st.pop_back();

            scc.push_back(top);
            sccIdx[top] = sccs.size();
            finish[top] = true;

            if(top == cur) break;
        }
    }
    return ret;
};
for(int i = 0; i < n; ++i) {
    if(d[i] == 0) scc_dfs(scc_dfs, i);
}
