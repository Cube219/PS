DSU dsu(n);
for(auto& bcc : bccs) {
    if(bcc.size() == 1) continue;
    for(auto [u, v] : bcc) dsu.uni(u, v);
}
vector<vector<int>> g2(n);
for(auto& bcc : bccs) {
    if(bcc.size() != 1) continue;
    auto [u, v] = bcc[0];
    u = dsu.find(u); v = dsu.find(v);

    g[u].push_back(v);
    g[v].push_back(u);
}
