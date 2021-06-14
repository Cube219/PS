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
ll d[100001];

ll tfunc(ll x)
{
    ll cur = 0;
    ll res = 0;
    for(int i = 1; i < n; ++i) {
        cur += x;
        res += abs(cur - d[i]);
    }
    return res;
}

ll tsearch(ll minv, ll maxv)
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
    for(ll i = l + 1; i <= r; ++i) {
        res = min(res, tfunc(i));
    }
    return res;
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
        cin >> d[i];
    }

    ll res = tsearch(1, 1000000000);
    cout << res;

    return 0;
}
