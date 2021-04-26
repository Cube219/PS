#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, d[300001];
int dp[300001][101];
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        res = max(res, d[i]);
    }

    dp[1][d[1]] = 1;
    for(int i = 2; i <= n; ++i) {
        dp[i][d[i]] = i;
        int cur = d[i];
        for(int j = i - 1; j > 0;) {
            if(dp[j][cur] != 0) {
                dp[i][cur + 1] = dp[j][cur];
                j = dp[j][cur] - 1;
                cur++;
                res = max(res, cur);
            } else {
                break;
            }
        }
    }

    cout << res;

    return 0;
}
