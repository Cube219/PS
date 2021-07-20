#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, d[501];
int dp[2][100005];
int sum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        sum += d[i];
    }
    for(int i = 0; i <= sum; ++i) {
        dp[0][i] = -1;
        dp[1][i] = -1;
    }
    dp[0][0] = 0;
    dp[1][0] = 0;
    for(int i = 1; i <= n; ++i) {
        int cur = i % 2;
        int pre = 1 - cur;
        int v = d[i - 1];
        for(int j = 0; j <= sum; ++j) {
            dp[cur][j] = dp[pre][j];
        }
        for(int j = 0; j <= sum; ++j) {
            if(dp[pre][j] == -1) continue;
            dp[cur][j + v] = max(dp[cur][j + v], dp[pre][j] + v);
            dp[cur][abs(j - v)] = max(dp[cur][abs(j - v)], dp[pre][j] + v);
        }
    }

    int res = dp[n % 2][0];
    res = res / 2 + (sum - res);

    cout << res;

    return 0;
}
