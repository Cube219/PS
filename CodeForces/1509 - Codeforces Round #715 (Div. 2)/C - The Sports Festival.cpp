#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 2000000007;

int n, d[2002];
vector<int> cur;
ll res;
ll dp[2002][2002], mn[2002][2002], mx[2002][2002];

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
    sort(d, d + n);

    for(int i = 0; i < n; ++i) {
        mn[i][i] = d[i];
        mx[i][i] = d[i];
    }
    for(int i = 2; i <= n; ++i) {
        for(int j = 0; j < n - i + 1; ++j) {
            int l = j;
            int r = l + i - 1;
            dp[l][r] = INF;

            ll left = dp[l][r - 1] + d[r] - mn[l][r - 1];
            ll right = dp[l + 1][r] + mx[l + 1][r] - d[l];
            if(left < right) {
                dp[l][r] = left;
                mx[l][r] = d[r];
                mn[l][r] = mn[l][r - 1];
            } else {
                dp[l][r] = right;
                mn[l][r] = d[l];
                mx[l][r] = mx[l + 1][r];
            }
        }
    }

    cout << dp[0][n-1] << "\n";

    return 0;
}
