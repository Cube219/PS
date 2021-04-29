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
ll a[5001], b[5001], ra[5001], tmp[5001];
ll dp[5001][5001];
ll res = 0;

void process(int l, int r)
{
    ll sum = dp[0][n - 1];
    if(l > r) return;
    int m = (l + r) / 2;
    int cl, cr;
    ll cur = 0;
    if((r - l + 1) % 2 == 1) {
        cl = m;
        cr = m;
        cur = -ra[m] * b[m];
    } else {
        cl = m;
        cr = m + 1;
    }
    while(1) {
        if(cl < 0 || cr >= n) break;
        cur += ra[cl] * b[cl] + ra[cr] * b[cr];

        sum -= dp[cl][cr];
        sum += cur;
        res = max(res, sum);
        sum += dp[cl][cr];
        sum -= cur;

        cl--;
        cr++;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        ra[i] = a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    reverse(ra, ra + n);

    for(int i = 0; i < n; ++i) {
        dp[i][i] = a[i] * b[i];
    }
    for(int sz = 2; sz <= n; ++sz) {
        int l = 0;
        int r = l + sz - 1;
        while(r < n) {
            dp[l][r] = dp[l][r - 1] + a[r] * b[r];
            //revdp[l][r] = revdp[l][r - 1] + ra[r] * b[r];
            l++; r++;
        }
    }

    int sz = n;
    for(int i = 0; i < n; ++i) {
        process(0, sz - 1);
        process(sz, n - 1);
        sz--;
        for(int j = 0; j < n; ++j) {
            tmp[j] = ra[(j + 1) % n];
        }
        for(int j = 0; j < n; ++j) {
            ra[j] = tmp[j];
        }
    }

    ll cur = dp[0][n - 1];

    // for(int sz = 2; sz <= n; ++sz) {
    //     int l = 0;
    //     int r = l + sz - 1;
    //     while(r < n) {
    //         cur -= dp[l][r];
    //         cur += revdp[l][r];
    //         res = max(res, cur);
    //         cur += dp[l][r];
    //         cur -= revdp[l][r];
    //
    //         l++; r++;
    //     }
    // }

    cout << res;

    return 0;
}
