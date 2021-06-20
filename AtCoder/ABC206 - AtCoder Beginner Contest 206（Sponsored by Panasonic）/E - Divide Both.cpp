#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll l, r;
ll mobi[1000001];

void init(ll r)
{
    for(ll i = 2; i <= r; ++i) {
        if(mobi[i] != 0) continue;
        for(ll j = i; j <= r; j += i) {
            mobi[j]++;
        }
        for(ll j = i * i; j <= r; j += i*i) {
            mobi[j] = -10000000;
        }
    }
    mobi[1] = 2;
}

ll copnum(ll l, ll r)
{
    ll res = 0;
    for(ll i = 1; i <= r; ++i) {
        if(mobi[i] <= 0) continue;
        ll v = r / i - (l - 1) / i;
        if(mobi[i] % 2 == 1) res -= v * v;
        else res += v * v;
    }

    return res / 2;
}

ll mulnum(ll l, ll r)
{
    ll res = 0;
    for(ll i = max(2LL, l); i <= r; ++i) {
        res += (r / i - 1);
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

    cin >> l >> r;
    init(r);

    ll sz = r - l;
    ll res = sz * (sz + 1) / 2;
    res -= copnum(l, r);
    res -= mulnum(l, r);

    cout << res * 2;

    return 0;
}
