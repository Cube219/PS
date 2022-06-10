vector<ll> dst;
auto dijk = [&](int n, int st) -> void {
    dst.resize(n, LNF);
    dst[st] = 0;
    struct PNode
    {
        int cur; ll cost;
        bool operator<(const PNode& rhs) const { return cost > rhs.cost; }
    };
    priority_queue<PNode> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        auto [cur, cost] = pq.top();
        pq.pop();
        if(dst[cur] != cost) continue;

        for(auto [nxt, cost] : g[cur]) {
            if(dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                pq.push({ dst[nxt], nxt });
            }
        }
    }
};
