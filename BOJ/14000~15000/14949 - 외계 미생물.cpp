#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

using lli = long long int;

int h, w;
// d[i][j] - i개인 상태에서, j만큼 번식할 수 있는 경우의 수 -> 결국 iHj(중복조합)랑 동치
lli d[401][401];
// dp[i][j] - i만큼 시간이 흐르고 j개수만큼 있을 수 있는 경우의 수
lli dp[6][401];

constexpr lli MOD = 1000000007;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> h >> w;

    for(int i = 0; i <= w; i++) {
        d[1][i] = 1;
    }
    
    for(int i = 2; i <= w; i++) {
        d[i][0] = 1;

        for(int j = 1; j <= w; j++) {
            for(int k = 0; k <= j; k++) {
                d[i][j] = (d[i][j] + d[i - 1][k]) % MOD;
            }
        }
    }

    dp[0][1] = 1;
    for(int i = 1; i <= w; i++) {
        dp[1][i] = 1;
    }

    for(int i = 1; i < h; i++) {
        for(int j = 1; j <= w; j++) {
            for(int k = 1; k <= w; k++) {
                dp[i + 1][k] = (dp[i + 1][k] + (dp[i][j] * d[j][k]) % MOD) % MOD;
            }
        }
    }

    lli res = 0;
    for(int i = 1; i <= w; i++) {
        res = (res + dp[h][i]) % MOD;
    }

    cout << res;

    return 0;
}
