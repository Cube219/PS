vector<int> idx(n);
vector<vector<int>> g2;
for(int i = 0; i < n; ++i) {
    if(isCut[i]) {
        g2.emplace_back();
        idx[i] = g2.size() - 1;
    }
}
unordered_map<ll, int> bridges;
vector<char> isUse(n, 0);
for(auto& b : bcc) {
    g2.emplace_back();
    int cur = g2.size() - 1;
    for(auto& p : b) {
        if(!isUse[p.first]) {
            if(isCut[p.first]) {
                g2[cur].emplace_back(idx[p.first]);
                g2[idx[p.first]].emplace_back(cur);
            } else idx[p.first] = cur;
            isUse[p.first] = true;
        }
        if(!isUse[p.second]) {
            if(isCut[p.second]) {
                g2[cur].emplace_back(idx[p.second]);
                g2[idx[p.second]].emplace_back(cur);
            } else idx[p.second] = cur;
            isUse[p.second] = true;
        }
    }
    if(b.size() == 1) {
        ll u = b[0].first;
        ll v = b[0].second;
        if(u > v) swap(u, v);
        bridges.insert({ u << 32 | v, cur });
    }
    for(auto& p : b) {
        isUse[p.first] = false;
        isUse[p.second] = false;
    }
}
