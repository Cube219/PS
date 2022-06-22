// req: psbipartite
auto cover = [&]() {
    vector<char> visitL(n, true), visitR(m, false);
    for(int i = 0; i < n; ++i) if(a[i] != -1) visitL[i] = false;
    queue<int> q;
    for(int i = 0; i < n; ++i) if(visitL[i]) q.push(i);
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        visitL[cur] = true;
        for(int nxt : g[cur]) {
            if(!visitR[nxt] && b[nxt] != -1) {
                visitR[nxt] = true;
                q.push(b[nxt]);
            }
        }
    }
    vector<int> res;
    for(int i = 0; i < n; ++i) if(!visitL[i]) res.push_back(i);
    for(int i = 0; i < m; ++i) if(visitR[i]) res.push_back(i + n);
    return res;
};
