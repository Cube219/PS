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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<char> zero(n + 1, false);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if(u == 0) {
            zero[v] = true;
        } else {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }

    auto dijk = [&](int st) {
        vector<int> dst(n + 1, INF);
        dst[st] = 0;
        struct PNode
        {
            int cur;
            int cost;
            bool operator<(const PNode& rhs) const { return cost > rhs.cost; }
        };
        priority_queue<PNode> pq;
        pq.push({ st, 0 });
        while(pq.empty() == false) {
            auto [cur, cost] = pq.top();
            pq.pop();
            if(dst[cur] != cost) continue;

            for(auto nxt : g[cur]) {
                if(dst[nxt] > dst[cur] + 1) {
                    dst[nxt] = dst[cur] + 1;
                    pq.push({ nxt, dst[nxt] });
                }
            }
        }

        return dst;
    };

    ;
    auto stDst = dijk(1);
    int stToZero = INF;
    for(int i = 1; i <= n; ++i) {
        if(zero[i]) stToZero = min(stToZero, stDst[i] + 1);
    }
   
    auto edDst = dijk(n);
    int edToZero = INF;
    for(int i = 1; i <= n; ++i) {
        if(zero[i]) edToZero = min(edToZero, edDst[i] + 1);
    }

    for(int i = 1; i <= n; ++i) {
        int res = stDst[n];
        res = min(res, stDst[i] + edToZero);
        res = min(res, stToZero + edDst[i]);
        res = min(res, stToZero + edToZero);

        if(res == INF) res = -1;
        cout << res << " ";
    }
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
