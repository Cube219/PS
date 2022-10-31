#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, x;
    cin >> n >> x;
    struct Nxt { int nxt, c; };
    vector<vector<Nxt>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    vector<int> sz(n), cost(n);
    vector<Nxt> par(n);
    vector<vector<int>> dp(n, vector<int>(20, 0));
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        sz[cur] = 1;
        
        for(auto [nxt, c] : g[cur]) {
            if(nxt == pre) continue;

            par[nxt] = { cur, c };
            cost[nxt] = cost[cur] ^ c;
            self(self, nxt, cur);
            sz[cur] += sz[nxt];

            for(int i = 0; i < 20; ++i) {
                if((c & (1 << i)) > 0) { // 1
                    dp[cur][i] += sz[nxt] - dp[nxt][i];
                } else {
                    dp[cur][i] += dp[nxt][i];
                }
            }
        }
    };
    par[0] = { -1, -1 };
    cost[0] = 0;
    dfs(dfs, 0, -1);

    int res = INF;
    for(int i = 0; i < n; ++i) {
        int cnt = 0;
        int xx = x ^ cost[i];
        for(int bit = 0; bit < 20; ++bit) {
            int mask = 1 << bit;

            int oneNum = dp[0][bit];
            int zeroNum = sz[0] - oneNum;
            if((xx & mask) > 0) cnt += zeroNum;
            else cnt += oneNum;
        }
        res = min(res, cnt);
    }

    cout << res;
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
