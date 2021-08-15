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

int n, h[500001];
ll dp[500001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    ll res = 1;
    int curh = h[0];
    dp[0] = 1;
    int lasti = 0;
    for(int i = 1; i < n; ++i) {
        if(curh < h[i]) {
            dp[i] = (dp[lasti] * (i - lasti)) % MOD;
            dp[i] = (dp[i] + dp[lasti]) % MOD;
            res = dp[i];

            curh = h[i];
            lasti = i;
        }
    }

    cout << res;

    return 0;
}
