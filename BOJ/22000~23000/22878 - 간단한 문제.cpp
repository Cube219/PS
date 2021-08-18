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
int p[1000001], q[1000001], r[1000001], s[1000001];
ll res, dp[1000001];

ll sum(int* d)
{
    ll ret = 0;
    sort(d, d + n);

    for(int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1] + ((ll)(d[i] - d[i - 1]) * i);
        ret += dp[i];
    }

    return ret * 2;
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
        cin >> p[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> q[i];
    }
    for(int i = 0; i < n; ++i) {
        r[i] = p[i] + q[i];
    }
    for(int i = 0; i < n; ++i) {
        s[i] = p[i] - q[i];
    }

    res += sum(p);
    res += sum(q);
    res -= sum(r) / 2;
    res -= sum(s) / 2;

    cout << res;

    return 0;
}
