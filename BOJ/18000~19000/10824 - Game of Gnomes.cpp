#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll n, m, k;
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(ll knum = n / k; knum >= 0; --knum) {
        ll remain = n - knum * k;
        ll cur = knum * n - knum * (knum - 1) / 2 * k;
        if(knum == 0) cur = 0;

        ll v = remain / m;
        ll p1num = remain % m;
        if(p1num > 0 && v + 1 > k) break;
        if(p1num == 0 && v > k) break;

        cur += remain * p1num - p1num * (p1num - 1) / 2 * (v + 1);
        ll p0num = m - p1num;
        remain = v * p0num;
        cur += remain * p0num - p0num * (p0num - 1) / 2 * v;
        res = max(res, cur);
    }

    cout << res;

    return 0;
}
    