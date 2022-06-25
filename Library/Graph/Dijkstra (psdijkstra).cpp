auto dijk = [&](int st) {
    vector<ll> dst(n, LNF);
    dst[st] = 0;
    struct PNode
    {
        int cur;
        ll cost;
        bool operator<(const PNode& rhs) const { return cost > rhs.cost; }
    };
    priority_queue<PNode> pq;
    pq.push({ st, 0 });
    while(pq.empty() == false) {
        auto [cur, cost] = pq.top();
        pq.pop();
        if(dst[cur] != cost) continue;

        for(auto [nxt, cost] : g[cur]) {
            if(dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                pq.push({ nxt, dst[nxt] });
            }
        }
    }

    return dst;
};
