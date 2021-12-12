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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;
    cin >> n >> a >> b;
    vector<int> p(n), q(n), r(n), s(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i] >> q[i] >> r[i] >> s[i];
    }

    vector<vector<vector<vector<int>>>> dp(2);
    dp[0].resize(n + 1);
    dp[1].resize(n + 1);
    for(int i = 0; i <= n; ++i) {
        dp[0][i].resize(n + 1);
        dp[1][i].resize(n + 1);
        for(int j = 0; j <= n; ++j) {
            dp[0][i][j].resize(2, -INF);
            dp[1][i][j].resize(2, -INF);
        }
    }
    dp[0][0][0][0] = 0;
    dp[0][0][0][1] = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= n; ++j) {
            for(int k = 0; k <= n; ++k) {
                dp[1][j][k][0] = 0;
                // p
                dp[1][j][k][0] = max(dp[1][j][k][0], dp[0][j][k][0] + p[i]);
                dp[1][j][k][0] = max(dp[1][j][k][0], dp[0][j][k][1] + p[i]);

                // q
                dp[1][j][k][0] = max(dp[1][j][k][0], dp[0][j][k][0] + q[i]);
                dp[1][j][k][0] = max(dp[1][j][k][0], dp[0][j][k][1] + q[i]);

                // s
                if(k > 0) {
                    dp[1][j][k][0] = max(dp[1][j][k][0], dp[0][j][k - 1][0] + s[i]);
                    dp[1][j][k][0] = max(dp[1][j][k][0], dp[0][j][k - 1][1] + s[i]);
                }

                // r
                dp[1][j][k][1] = 0;
                if(j > 0) {
                    dp[1][j][k][1] = dp[0][j - 1][k][0] + r[i];
                }
            }
        }

        swap(dp[0], dp[1]);
    }

    int res = 0;
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= n; ++j) {
            if(i + j > n - b) break;
            if(j > a) break;

            res = max(res, dp[0][i][j][0]);
            res = max(res, dp[0][i][j][1]);
        }
    }

    cout << res;

    return 0;
}
