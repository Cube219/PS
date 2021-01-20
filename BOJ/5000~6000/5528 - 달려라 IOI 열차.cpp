#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

using lli = long long int;

int n, m;
char a1[2002], a2[2002];
int dp[2001][2001][2];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> a1 >> a2;

    for(int i = n; i >= 0; i--) {
        for(int j = m; j >= 0; j--) {
            int oMax = 0;
            int iMax = 0;
            if(a1[i] == 'I' || a2[j] == 'I') iMax = 1;

            // a1을 쓰는 경우
            if(i != n) {
                if(a1[i] == 'O') {
                    if(dp[i + 1][j][1] > 0 && oMax < dp[i + 1][j][1] + 1) oMax = dp[i + 1][j][1] + 1;
                } else {
                    if(iMax < dp[i + 1][j][0] + 1) iMax = dp[i + 1][j][0] + 1;
                }
            }

            // a2를 쓰는 경우
            if(j != m) {
                if(a2[j] == 'O') {
                    if(dp[i][j + 1][1] > 0 && oMax < dp[i][j + 1][1] + 1) oMax = dp[i][j + 1][1] + 1;
                } else {
                    if(iMax < dp[i][j + 1][0] + 1) iMax = dp[i][j + 1][0] + 1;
                }
            }

            dp[i][j][0] = oMax;
            dp[i][j][1] = iMax;

            if(res < iMax) res = iMax;
        }
    }

    cout << res;

    return 0;
}
