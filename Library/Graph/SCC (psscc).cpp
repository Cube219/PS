vector<int> dep(n, 0), st, finish(n, false), sccIdx(n);
vector<vector<int>> sccs;
int dNum = 0;

auto scc_dfs = [&](auto&& self, int cur) -> int {
    dep[cur] = ++dNum;
    st.push_back(cur);

    int ret = dep[cur];
    for(int nxt : g[cur]) {
        if(dep[nxt] == 0) ret = min(ret, self(self, nxt));
        else if(finish[nxt] == false) ret = min(ret, dep[nxt]);
    }

    if(ret == dep[cur]) {
        sccs.push_back({});
        auto& scc = sccs.back();
        while(1) {
            int top = st.back();
            st.pop_back();

            scc.push_back(top);
            sccIdx[top] = (int)sccs.size() - 1;
            finish[top] = true;

            if(top == cur) break;
        }
    }
    return ret;
};
for(int i = 0; i < n; ++i) {
    if(dep[i] == 0) scc_dfs(scc_dfs, i);
}
