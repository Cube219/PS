#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 87654321;

int n, m;
vector<int> g[202];
int dp[202][202];
int res = INF;
int tmp[202];

void p(int cur, int par)
{
    dp[cur][1] = g[cur].size();

    for(int nxt : g[cur]) {
        if(nxt == par) continue;

        p(nxt, cur);
        for(int i = 1; i <= m; ++i) {
            tmp[i] = dp[cur][i];
        }
        for(int i = 1; i <= m; ++i) {
            for(int j = 1; j < i; ++j) {
                tmp[i] = min(tmp[i], dp[nxt][j] + dp[cur][i - j] - 2);
            }
        }
        for(int i = 1; i <= m; ++i) {
            dp[cur][i] = tmp[i];
        }
    }

}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= m; ++j) {
            dp[i][j] = INF;
        }
    }
    p(1, -1);
    for(int i = 1; i <= n; ++i) {
        res = min(res, dp[i][m]);
    }

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
