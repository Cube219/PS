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
    struct Node
    {
        int nxt;
        int v;
    };
    vector<vector<Node>> g(n);
    vector<int> in(n, 0);
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g[u].push_back({ v, c });
        in[v]++;
    }

    vector<int> dp(n, 0);
    queue<int> q;
    for(int i = 0; i < n; ++i) {
        if(in[i] == 0) {
            q.push(i);
        }
    }

    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        for(auto [nxt, cost] : g[cur]) {
            if(dp[nxt] < dp[cur] + cost) {
                dp[nxt] = dp[cur] + cost;
            }
            in[nxt]--;
            if(in[nxt] == 0) q.push(nxt);
        }
    }

    int res = 0;
    for(int i = 0; i < n; ++i) {
        res = max(res, dp[i]);
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
