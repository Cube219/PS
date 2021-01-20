#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, d[1002];
int dp[1002], dpNum;

int lisRev(int ed, int min)
{
    int res = 1;
    dp[0] = 0;
    dp[1] = min;
    dpNum = 2;

    for(int i = ed - 1; i >= 1; i--) {
        if(d[i] <= min) continue;

        auto it = lower_bound(dp, dp + dpNum, d[i]);
        *it = d[i];
        if(it == dp + dpNum) {
            dpNum++;
        }
    }

    return dpNum - 1;
}

int lis(int st, int min)
{
    int res = 1;
    dp[0] = 0;
    dp[1] = min;
    dpNum = 2;

    for(int i = st + 1; i <= n; i++) {
        if(d[i] <= min) continue;

        auto it = lower_bound(dp, dp + dpNum, d[i]);
        *it = d[i];
        if(it == dp + dpNum) {
            dpNum++;
        }
    }

    return dpNum - 1;
}

int res = 0;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    for(int i = 1; i <= n; i++) {
        int r = lisRev(i, d[i]) + lis(i, d[i]) - 1;
        if(res < r) res = r;
    }

    cout << res;

    return 0;
}
