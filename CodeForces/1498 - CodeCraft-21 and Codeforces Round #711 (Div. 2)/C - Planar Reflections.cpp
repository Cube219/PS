#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll MOD = 1'000'000'007;

int tNum;
int n, k;
ll dp[1001][1001][2];
// i: 수명 / j: 통과할 벽의 수 / k: 왼/오른쪽
void process()
{
    for(int i = 0; i <= n; ++i) {
        dp[1][i][0] = 1;
        dp[1][i][1] = 1;
    }
    for(int i = 2; i <= k; ++i) {
        dp[i][0][0] = 1;
        dp[i][0][1] = 1;
        for(int j = 1; j <= n; ++j) {
            dp[i][j][0] = (dp[i][j - 1][0] + dp[i - 1][n - j][1]) % MOD;
        }
        for(int j = 1; j <= n; ++j) {
            dp[i][j][1] = (dp[i][j - 1][1] + dp[i - 1][n - j][0]) % MOD;
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

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        process();
        cout << dp[k][n][0] << "\n";
    }

    return 0;
}
