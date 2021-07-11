#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000000 + 7;

int n, d[4001];
ll dp[4001][4001];
ll sum[4001][4001];

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
    }

    dp[0][0] = 1;
    sum[0][0] = 1;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(d[i - 1] == d[i]) {
                dp[i][j] += sum[i - 1][i - 1];
            } else if(d[i - 1] < d[i]) {
                dp[i][j] += sum[i - 1][i - 1];
                if(j > 0) {
                    dp[i][j] -= sum[i - 1][j - 1];
                    dp[i][j] += MOD;
                }
            } else { // d[i - 1] > d[i]
                if(j > 0) {
                    dp[i][j] += sum[i - 1][j - 1];
                }
            }
            dp[i][j] %= MOD;
            if(j > 0) sum[i][j] = sum[i][j - 1];
            sum[i][j] += dp[i][j];
            sum[i][j] %= MOD;
        }
    }

    cout << sum[n - 1][n - 1];

    return 0;
}
