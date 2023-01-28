#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m, t;
    cin >> n >> m >> t;
    struct Nxt
    {
        int nxt, t, s, defaultS;
    };
    vector<vector<Nxt>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v, t, s;
        cin >> u >> v >> t >> s;
        u--; v--;
        g[u].push_back({ v, t, s, s });
        g[v].push_back({ u, t, s, s });
    }

    vector<ll> dst(n);
    auto dijk = [&](int st) {
        fill(dst.begin(), dst.end(), LNF);
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

            for(auto [nxt, cost, _1, _2] : g[cur]) {
                if(dst[nxt] > dst[cur] + cost) {
                    dst[nxt] = dst[cur] + cost;
                    pq.push({ nxt, dst[nxt] });
                }
            }
        }
    };

    auto ck = [&](int x) {
        for(auto& v : g) {
            for(auto& v2 : v) {
                v2.t -= v2.defaultS - v2.s;
                v2.s = v2.defaultS;

                if(v2.s > x) {
                    int gap = v2.s - x;
                    v2.s -= gap;
                    v2.t += gap;
                }
            }
        }

        dijk(0);
        return (dst[n - 1] <= t);
    };

    int lo = -1, hi = 1000000001;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(ck(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    if(hi == 1000000001) hi = -1;
    cout << hi;
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
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
