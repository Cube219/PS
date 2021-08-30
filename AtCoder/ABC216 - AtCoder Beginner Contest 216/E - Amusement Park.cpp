#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll n, k;
ll a[100001];

ll getv(ll mx, ll mn, ll cnt)
{
    ll res = 0;
    ll sum1 = mx * (mx + 1) / 2;
    ll sum2 = (mn - 1) * mn / 2;
    res = sum1 - sum2;
    return res * cnt;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a, a + 1 + n);

    ll res = 0;
    ll cnt = 1;
    for(int i = n; i >= 1; --i) {
        ll gap = a[i] - a[i - 1];

        ll v = gap * cnt;
        if(v <= k) {
            k -= v;
            res += getv(a[i], a[i - 1] + 1, cnt);
        } else {
            ll rownum = k / cnt;
            res += getv(a[i], a[i] - rownum + 1, cnt);
            k -= rownum * cnt;

            a[i] -= rownum;
            res += a[i] * k;

            break;
        }
        cnt++;
    }

    cout << res;

    return 0;
}
