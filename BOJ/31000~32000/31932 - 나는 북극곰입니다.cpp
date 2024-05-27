#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    struct Graph
    {
        int nxt, d, t;
    };
    vector<vector<Graph>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, d, t;
        cin >> u >> v >> d >> t;
        u--;
        v--;
        g[u].push_back({v, d, t});
        g[v].push_back({u, d, t});
    }

    auto dijk = [&](int st, int offset) {
        vector<ll> dst(n, LNF);
        dst[st] = 0;
        struct PNode
        {
            int cur;
            ll cost;
            bool operator<(const PNode& rhs) const
            {
                return cost > rhs.cost;
            }
        };
        priority_queue<PNode> pq;
        pq.push({st, 0});
        while (pq.empty() == false) {
            auto [cur, cost] = pq.top();
            pq.pop();
            if (dst[cur] != cost) continue;

            for (auto [nxt, cost, t] : g[cur]) {
                if (t >= dst[cur] + offset + cost && dst[nxt] > dst[cur] + cost) {
                    dst[nxt] = dst[cur] + cost;
                    pq.push({nxt, dst[nxt]});
                }
            }
        }

        return dst;
    };

    int lo = -1, hi = 1000000001;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        auto dst = dijk(0, mid);

        if (dst[n - 1] == LNF) hi = mid;
        else lo = mid;
    }

    cout << lo;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
