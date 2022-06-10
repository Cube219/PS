vector<int> par(n);
iota(par.begin(), par.end(), 0);
auto find = [&](int a) {
    vector<int> st;
    while(par[a] != a) {
        st.push_back(a);
        a = par[a];
    }
    for(int v : st) par[v] = a;
    return a;
};
auto uni = [&](int a, int b) {
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;
    par[br] = ar;
};
for(auto& bc : bcc) {
    if(bc.size() == 1) continue;
    for(auto& p : bc) uni(p.first, p.second);
}
vector<vector<int>> g2(n);
for(auto& bc : bcc) {
    if(bc.size() != 1) continue;
    int a = find(bc[0].first);
    int b = find(bc[0].second);

    g2[a].push_back(b);
    g2[b].push_back(a);
}
