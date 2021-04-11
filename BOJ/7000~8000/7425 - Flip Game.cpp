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

int n, m;
int map[5][5];
int bitmap[5];
int dp[5][1 << 5], press[1001][1 << 5];
char str[10];

int solve()
{
    for(int i = 0; i < n; ++i) {
        bitmap[i] = 0;
        for(int j = 0; j < m; ++j) {
            bitmap[i] <<= 1;
            bitmap[i] |= map[i][j];
        }
    }

    for(int i = 0; i < 1 << m; ++i) {
        dp[0][i] = INF;
    }

    for(int i = 0; i < 1 << m; ++i) {
        int bitNum = 0;
        int cur = bitmap[0];
        for(int j = 0; j < m; ++j) {
            int bit = 1 << j;
            if((i & bit) > 0) {
                bitNum++;
                cur = cur ^ bit;
                if(j > 0) cur = cur ^ (bit >> 1);
                if(j < m - 1) cur = cur ^ (bit << 1);
            }
        }
        if(dp[0][cur] > bitNum) {
            dp[0][cur] = bitNum;
            press[0][cur] = i;
        }
    }

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < 1 << m; ++j) {
            dp[i][j] = INF;
        }
        int init = bitmap[i];

        for(int j = 0; j < 1 << m; ++j) {
            int cur = init;
            int bitNum = 0;
            for(int k = 0; k < m; ++k) {
                int bit = 1 << k;
                if((j & bit) > 0) {
                    bitNum++;
                    cur = cur ^ bit;
                    if(k > 0) cur = cur ^ (bit >> 1);
                    if(k < m - 1) cur = cur ^ (bit << 1);
                }
            }
            int beforePress = press[i - 1][j];
            for(int k = 0; k < m; ++k) {
                int bit = 1 << k;
                if((beforePress & bit) > 0) {
                    cur = cur ^ bit;
                }
            }
            if(dp[i][cur] > dp[i - 1][j] + bitNum) {
                dp[i][cur] = dp[i - 1][j] + bitNum;
                press[i][cur] = j;
            }
        }
    }
    return dp[n - 1][0];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    n = 4;
    m = 4;
    for(int i = 0; i < n; ++i) {
        cin >> str;
        for(int j = 0; j < m; ++j) {
            if(str[j] == 'b') map[i][j] = 0;
            else map[i][j] = 1;
        }
        for(int j = 0; j < m; ++j) {
            bitmap[i] <<= 1;
            bitmap[i] |= map[i][j];
        }
    }
    int res = solve();

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            map[i][j] = 1 - map[i][j];
        }
    }

    res = min(res, solve());
    if(res == INF) cout<<"Impossible";
    else cout << res;

    return 0;
}
