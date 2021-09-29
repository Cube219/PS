#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, k;
ll d[20001], dp[20001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
    }

    for(int i = 1; i <= n; ++i) {
        ll mx = d[i];
        ll mn = d[i];
        dp[i] = dp[i - 1] + k;

        for(int j = 2; j <= m; ++j) {
            if(i - j < 0) break;
            mx = max(mx, d[i - j + 1]);
            mn = min(mn, d[i - j + 1]);
            dp[i] = min(dp[i], dp[i - j] + (mx - mn) * j + k);
        }
    }

    cout << dp[n];

    return 0;
}
