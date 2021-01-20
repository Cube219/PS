#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n, a[200001], dp[200001][2]; // 0: friend / 1:my
int r[200001][2];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            dp[i][0] = 0;
            dp[i][1] = 0;
        }

        dp[1][0] = a[1];
        dp[1][1] = 987654321;
        if(n > 1) {
            dp[2][0] = a[1] + a[2];
            dp[2][1] = a[1];
            r[2][1] = 1;
        }

        for(int i = 3; i <= n; i++) {
            int two = a[i] + a[i - 1];
            int one = a[i];

            dp[i][0] = two + dp[i - 2][1];
            r[i][0] = i - 2;
            if(dp[i][0] > one + dp[i - 1][1]) {
                dp[i][0] = one + dp[i - 1][1];
                r[i][0] = i - 1;
            }

            dp[i][1] = min(dp[i - 1][0], dp[i - 2][0]);
            if(dp[i - 1][0] < dp[i - 2][1]) {
                r[i][1] = i - 1;
            } else {
                r[i][1] = i - 2;
            }
        }

        cout << min(dp[n][0], dp[n][1]) << "\n";
    }

    return 0;
}
