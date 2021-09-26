#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
string str;
ll res;
ll dp[100005][3];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    for(int i = 0; i < n; ++i) {
        if(i > 0) {
            for(int j = 0; j < 3; ++j) {
                dp[i][j] = dp[i - 1][j];
            }
        }
        if(str[i] == 'J') {
            dp[i][0]++;
        } else if(str[i] == 'O') {
            dp[i][1] += dp[i][0];
        } else {
            dp[i][2] += dp[i][1];
        }
    }
    res += dp[n - 1][2];
    ll mx = 0;
    mx = max(mx, dp[n - 1][1]);

    dp[n][0] = 0;
    dp[n][1] = 0;
    for(int i = n - 1; i >= 0; --i) {
        for(int j = 0; j < 2; ++j) {
            dp[i][j] = dp[i + 1][j];
        }

        if(str[i] == 'I') {
            dp[i][0]++;
        } else if(str[i] == 'O') {
            dp[i][1] += dp[i + 1][0];
        }
    }
    mx = max(mx, dp[0][1]);

    ll lnum = 0, rnum = 0;
    for(int i = 0; i < n; ++i) {
        if(str[i] == 'I') rnum++;
    }
    for(int i = 0; i < n; ++i) {
        mx = max(mx, lnum * rnum);
        if(str[i] == 'I') rnum--;
        if(str[i] == 'J') lnum++;
    }

    cout << res + mx;

    return 0;
}
