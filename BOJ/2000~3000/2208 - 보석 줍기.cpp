#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
ll d[100001];
ll sum[100001];
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sum[0] = d[0];
    for(int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + d[i];
    }
    ll mn = min(0LL, sum[0]);
    res = max(0LL, sum[m - 1]);
    for(int i = m; i < n; ++i) {
        res = max(res, sum[i] - mn);
        mn = min(mn, sum[i - m + 1]);
    }

    cout << res;

    return 0;
}
