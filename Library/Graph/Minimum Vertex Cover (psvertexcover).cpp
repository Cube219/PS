// req: psbipartite
auto cover = [&]() {
    vector<char> visitA(n, false), visitB(m, false);
    queue<int> q;
    for(int i = 0; i < n; ++i) if(a[i] == -1) q.push(i);
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        visitA[cur] = true;
        for(int nxt : g[cur]) {
            if(b[nxt] != -1 && !visitB[nxt]) {
                visitB[nxt] = true;
                q.push(b[nxt]);
            }
        }
    }
    vector<int> res;
    for(int i = 0; i < n; ++i) if(!visitA[i]) res.push_back(i);
    for(int i = 0; i < m; ++i) if(visitB[i]) res.push_back(n + i);
    return res;
};
