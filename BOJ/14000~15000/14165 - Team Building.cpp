#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000009;

int n, m, k;
int a[1001], b[1001];
ll dp[1001][1001], pre[1001][1001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(a, a + n);
    sort(b, b + m);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(a[i] > b[j]) {
                dp[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            pre[i][j] = dp[i][j];
            dp[i][j] = 0;
            if(i > 0) {
                pre[i][j] = (pre[i][j] + pre[i - 1][j]) % MOD;
            }
            if(j > 0) {
                pre[i][j] = (pre[i][j] + pre[i][j - 1]) % MOD;
            }
            if(i > 0 && j > 0) {
                pre[i][j] = (pre[i][j] - pre[i - 1][j - 1] + MOD) % MOD;
            }
        }
    }

    for(int kk = 1; kk < k; ++kk) {
        for(int i = 1; i < n; ++i) {
            for(int j = 1; j < m; ++j) {
                if(a[i] <= b[j]) continue;
                dp[i][j] = pre[i - 1][j - 1];
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                pre[i][j] = dp[i][j];
                dp[i][j] = 0;
                if(i > 0) {
                    pre[i][j] = (pre[i][j] + pre[i - 1][j]) % MOD;
                }
                if(j > 0) {
                    pre[i][j] = (pre[i][j] + pre[i][j - 1]) % MOD;
                }
                if(i > 0 && j > 0) {
                    pre[i][j] = (pre[i][j] - pre[i - 1][j - 1] + MOD) % MOD;
                }
            }
        }
    }

    cout << pre[n - 1][m - 1];

    return 0;
}
