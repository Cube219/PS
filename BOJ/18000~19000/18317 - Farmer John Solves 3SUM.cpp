#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;

int n, d[5001], q;
ll dp[5001][5001];

int num[4000005];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    for(int sz = 3; sz <= n; ++sz) {
        int l = 0;
        int r = sz - 1;
        for(int i = l + 1; i < r; ++i) {
            num[d[i] + 2000000]++;
        }
        while(r < n) {
            int lrv = -(d[l] + d[r]) + 2000000;
            dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + num[lrv];

            num[d[l + 1] + 2000000]--;
            num[d[r] + 2000000]++;
            l++;
            r++;
        }
        for(int i = l + 1; i < r; ++i) {
            num[d[i] + 2000000]--;
        }
    }

    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << dp[a][b] << "\n";
    }

    return 0;
}
