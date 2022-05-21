#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

#ifdef _WIN32
#define __builtin_popcount __popcnt
#endif

void solve()
{
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> g(n, vector<int>(n, 0));
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u][v]++;
        g[v][u]++;
    }
    vector<int> mx(n + 1, -1), mxMask(n + 1, 0);
    for(int mask = 0; mask < 1 << n; ++mask) {
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if((mask & (1 << i)) == 0) continue;
                if((mask & (1 << j)) == 0) continue;

                cnt += g[i][j];
            }
        }

        int num = __builtin_popcount(mask);
        if(mx[num] < cnt) {
            mx[num] = cnt;
            mxMask[num] = mask;
        }
    }

    vector<int> dp(s + 1, -1), rec(s + 1, -1);
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j + i <= s; ++j) {
            if(dp[j + i] < dp[j] + mx[i]) {
                dp[j + i] = dp[j] + mx[i];
                rec[j + i] = i;
            }
        }
    }

    vector<int> res(n, 0);
    int remain = s;
    while(rec[remain] != -1) {
        int cur = rec[remain];
        remain -= cur;
        int mask = mxMask[cur];
        for(int i = 0; i < n; ++i) {
            if(mask & (1 << i)) {
                res[i]++;
            }
        }
    }

    for(int v : res) cout << v << " ";
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
