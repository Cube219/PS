#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve(int n, int m)
{
    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());
    for(int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        g[u].emplace_back(v, t);
        g[v].emplace_back(u, t);
    }

    vector<vector<int>> g2(n, vector<int>(n, INF));
    for(int i = 0; i < n; ++i) {
        g2[i][i] = 0;
        for(auto [nxt, cost] : g[i]) {
            g2[i][nxt] = cost;
        }
    }
    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(g2[i][j] > g2[i][k] + g2[k][j]) g2[i][j] = g2[i][k] + g2[k][j];
            }
        }
    }

    vector<vector<int>> dp1(n - 2, vector<int>(1 << (n - 2), -1));
    vector<vector<int>> dp2(n - 2, vector<int>(1 << (n - 2), -1));
    struct Node
    {
        int cur, mask, cost;
        bool operator<(const Node& rhs) const
        {
            return cost > rhs.cost;
        }
    };

    for(int i = 0; i < n - 2; ++i) {
        dp1[i][1 << i] = g2[0][i + 1];
        dp2[i][1 << i] = g2[n - 1][i + 1];
    }
    auto p1 = [&](auto&& self, int cur, int mask) -> int {
        if(dp1[cur][mask] != -1) return dp1[cur][mask];

        int myMask = 1 << cur;
        int res = INF;
        for(int i = 0; i < n - 2; ++i) {
            if(i == cur || (mask & (1 << i)) == 0) continue;
            res = min(res, self(self, i, mask ^ myMask) + g2[cur + 1][i + 1]);
        }
        dp1[cur][mask] = res;
        return res;
    };
    auto p2 = [&](auto&& self, int cur, int mask) -> int {
        if(dp2[cur][mask] != -1) return dp2[cur][mask];

        int myMask = 1 << cur;
        int res = INF;
        for(int i = 0; i < n - 2; ++i) {
            if(i == cur || (mask & (1 << i)) == 0) continue;
            res = min(res, self(self, i, mask ^ myMask) + g2[cur + 1][i + 1]);
        }
        dp2[cur][mask] = res;
        return res;
    };

    int res = INF;
    for(int i = 0; i < 1 << (n - 2); ++i) {
        int cnt = 0;
        for(int cur = i; cur > 0; cur >>= 1) if(cur & 1) cnt++;
        if(cnt != (n - 2) / 2) continue;

        int m1 = i;
        int m2 = ((1 << (n - 2)) - 1) ^ m1;

        int v1 = INF, v2 = INF;
        for(int j = 0; j < n - 2; ++j) {
            if((m2 & (1 << j)) == 0) continue;
            v1 = min(v1, p1(p1, j, m1 | (1 << j)) + p2(p2, j, m2));
        }
        for(int j = 0; j < n - 2; ++j) {
            if((m2 & (1 << j)) == 0) continue;
            v2 = min(v2, p1(p1, j, m2) + p2(p2, j, m1 | (1 << j)));
        }
        res = min(res, v1 + v2);
    }

    cout << res << "\n";
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
    for(int tt = 1; ; tt++) {
        int n, m;
        cin >> n >> m;
        if(cin.eof()) break;

        cout << "Case " << tt << ": ";
        solve(n, m);
    }

    return 0;
}
