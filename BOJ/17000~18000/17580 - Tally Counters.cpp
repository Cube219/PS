#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

ll n, m, k;
ll a[1005], b[1005];
ll dp[1005][1005];
ll minv[1005];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> m;
        if(n == 0) break;

        k = n;

        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            a[i]--;
        }
        for(int i = 0; i < n; ++i) {
            cin >> b[i];
            b[i]--;
        }

        for(int i = 0; i < n; ++i) {
            a[i] = b[i] - a[i];
            if(a[i] < 0) a[i] += m;
        }

        for(int i = 0; i < k; ++i) {
            dp[0][i] = a[0] + m * i;
        }
        minv[k] = INF;
        for(int i = k - 1; i >= 0; --i) {
            minv[i] = minv[i + 1];
            minv[i] = min(minv[i], dp[0][i]);
        }

        for(int i = 1; i < n; ++i) {
            ll mv = INF;
            for(int j = 0; j < k; ++j) {
                dp[i][j] = mv;
                ll remain = max(0LL, a[i] - a[i - 1]);
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + remain);
                dp[i][j] = min(dp[i][j], minv[j + 1]);

                mv += m;
                mv = min(mv, a[i] - a[i - 1] + m + dp[i - 1][j]);
            }
            for(int j = k - 1; j >= 0; --j) {
                minv[j] = minv[j + 1];
                minv[j] = min(minv[j], dp[i][j]);
            }
        }
        ll res = INF;
        for(int i = 0; i < k; ++i) {
            res = min(res, dp[n - 1][i]);
        }
        cout << res << "\n";
    }

    return 0;
}
