#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

ll w, h, l;
ll res;

ll get(ll r)
{
    ll ret = 0;
    for(ll x = 0; x <= r; ++x) {
        ll y = (ll)sqrtl(r * r - x * x);
        ret += y + 1;
    }
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> w >> h >> l;

    res += get(l);
    res -= 1;

    res += get(l);
    res -= l;
    res -= min(l + 1, h + 1);
    ll l2 = l - h;
    if(l2 > 0) {
        res += get(l2);
        res -= l2;
        res -= min(l2 + 1, w + 1);
    }

    res += get(l);
    res -= l;
    res -= min(l + 1, w + 1);
    ll l3 = l - w;
    if(l3 > 0) {
        res += get(l3);
        res -= l3;
        res -= min(l3 + 1, h + 1);
    }

    if(l - w - h > 0) {
        for(int x = 0; x <= l - w - h; ++x) {
            ll y1 = (ll)sqrtl(l2 * l2 - (x + w) * (x + w)) + 1;
            ll y2 = (ll)sqrtl(l3 * l3 - x * x) - h + 1;

            res -= min(y1, y2);
        }
        res++;
    }


    cout << res;

    return 0;
}
