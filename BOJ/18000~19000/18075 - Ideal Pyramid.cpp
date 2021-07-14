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
ll x[1001], y[1001], h[1001];
ll cx, cy;

ll tfunc(ll xx)
{
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        res = max(res, abs(xx - x[i]) + h[i]);
    }
    return res;
}

ll tfunc2(ll yy)
{
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        res = max(res, abs(yy - y[i]) + h[i]);
    }
    return res;
}

pair<ll, ll> tsearch(ll minv, ll maxv)
{
    ll l = minv, r = maxv;
    while(l + 2 < r) {
        ll p = (l * 2 + r) / 3;
        ll q = (l + r * 2) / 3;

        ll pv = tfunc(p);
        ll qv = tfunc(q);
        if(pv <= qv) r = q;
        else l = p;
    }

    ll res = tfunc(l);
    ll r2 = l;
    for(ll i = l + 1; i <= r; ++i) {
        ll tmp = tfunc(i);
        if(res > tmp) {
            res = tmp;
            r2 = i;
        }
    }
    return { res, r2 };
}

pair<ll, ll> tsearch2(ll minv, ll maxv)
{
    ll l = minv, r = maxv;
    while(l + 2 < r) {
        ll p = (l * 2 + r) / 3;
        ll q = (l + r * 2) / 3;

        ll pv = tfunc2(p);
        ll qv = tfunc2(q);
        if(pv <= qv) r = q;
        else l = p;
    }

    ll res = tfunc2(l);
    ll r2 = l;
    for(ll i = l + 1; i <= r; ++i) {
        ll tmp = tfunc2(i);
        if(res > tmp) {
            res = tmp;
            r2 = i;
        }
    }
    return { res, r2 };
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
        cin >> x[i] >> y[i] >> h[i];
    }

    auto r1 = tsearch(-100000000, 100000000);
    auto r2 = tsearch2(-100000000, 100000000);

    cx = r1.second;
    cy = r2.second;
    ll hei = max(r1.first, r2.first);

    cout << cx << " " << cy << " " << hei;

    return 0;
}
