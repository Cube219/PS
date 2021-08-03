#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int tNum;
int a, b;
ll dp[501][50001];
ll dpsum[501][50001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dp[0][0] = 1;
    for(int i = 1; i <= 500; ++i) {
        for(int j = 0; j <= 50000; ++j) {
            dp[i][j] = dp[i - 1][j];
        }
        for(int j = i; j <= 50000; ++j) {
            dp[i][j] += dp[i - 1][j - i];
            dp[i][j] %= MOD;
        }

        dpsum[i][0] = dp[i][0];
        for(int j = 1; j <= 50000; ++j) {
            dpsum[i][j] = dpsum[i][j - 1] + dp[i][j];
            dpsum[i][j] %= MOD;
        }
    }

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b;

        ll res = 0;
        int curtotal = 0;
        for(int i = 1; i <= 500; ++i) {
            curtotal += i;
            if(a + b < curtotal) break;

            int r = min(curtotal, a);
            int l = min(curtotal, b);
            l = curtotal - l;
            l--;

            res += dpsum[i][r];
            if(l >= 0) {
                res += (-dpsum[i][l] + MOD);
            }
            res %= MOD;
        }

        cout << res << "\n";
    }

    return 0;
}
