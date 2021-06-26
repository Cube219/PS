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

int n, t, v[101], c[101];
int dp[20001][2], dp2[20001], cnt[20001];
int res = INF;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 1; i < 20000; ++i) {
        dp2[i] = INF;
        dp[i][0] = INF;
        dp[i][1] = INF;
    }

    cin >> n >> t;
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = v[i]; j < 20000; ++j) {
            dp2[j] = min(dp2[j], dp2[j - v[i]] + 1);
        }
    }

    for(int i = 0; i < n; ++i) {
        int cur = i % 2;
        int pre = 1 - cur;
        for(int j = 0; j < 20000; ++j) {
            cnt[j] = 0;
        }
        for(int j = 0; j < v[j]; ++j) {
            dp[j][cur] = dp[j][pre];
        }
        for(int j = v[i]; j < 20000; ++j) {
            dp[j][cur] = dp[j][pre];
            if(c[i] > 0 && dp[j][cur] > dp[j-v[i]][pre] + 1) {
                dp[j][cur] = dp[j - v[i]][pre] + 1;
                cnt[j] = 1;
            }
            if(cnt[j - v[i]] < c[i] && dp[j][cur] > dp[j - v[i]][cur] + 1) {
                dp[j][cur] = dp[j - v[i]][cur] + 1;
                cnt[j] = cnt[j - v[i]] + 1;
            }
        }
    }

    int cur = (n - 1) % 2;
    for(int i = t; i < 20000; ++i) {
        res = min(res, dp[i][cur] + dp2[i - t]);
    }

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
