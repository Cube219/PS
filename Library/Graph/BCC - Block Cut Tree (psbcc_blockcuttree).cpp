vector<vector<int>> g2;
vector<int> idx(n);
for(int i = 0; i < n; ++i) {
    if(isCut[i]) {
        idx[i] = g2.size();
        g2.push_back({});
    }
}
vector<char> use(n, false);
for(auto& bcc : bccs) {
    int cur = g2.size();
    g2.push_back({});
    for(auto [u, v] : bcc) {
        if(!use[u]) {
            if(isCut[u]) {
                g[idx[u]].push_back(cur);
                g[cur].push_back(idx[u]);
            } else idx[u] = cur;
            use[u] = true;
        }
        if(!use[v]) {
            if(isCut[v]) {
                g[idx[v]].push_back(cur);
                g[cur].push_back(idx[v]);
            } else idx[v] = cur;
            use[v] = true;
        }
    }
    for(auto [u, v] : bcc) {
        use[u] = false;
        use[v] = false;
    }
}
