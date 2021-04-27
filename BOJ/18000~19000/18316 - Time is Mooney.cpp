#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct Edge
{
    int s, e;
};

int n, m, c;
int d[1001];
Edge e[2002];
int dp[1001][1001];
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> c;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        e[i] = { a, b };
    }
    for(int i = 1; i < n; ++i) {
        dp[i][0] = -1;
    }

    for(int t = 1; t <= 1000; ++t) {
        for(int i = 0; i < n; ++i) {
            dp[i][t] = -1;
        }
        for(int i = 0; i < m; ++i) {
            int st = e[i].s;
            int ed = e[i].e;
            if(dp[st][t - 1] == -1) continue;
            dp[ed][t] = max(dp[ed][t], dp[st][t - 1] + d[ed]);
        }
        res = max(res, dp[0][t] - c * t * t);
    }

    cout << res;

    return 0;
}
