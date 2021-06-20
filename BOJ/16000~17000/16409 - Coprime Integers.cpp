#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;

ll mobi[10000001];

void init(ll r)
{
    for(ll i = 2; i <= r; ++i) {
        if(mobi[i] != 0) continue;
        for(ll j = i; j <= r; j += i) {
            mobi[j]++;
        }
        for(ll j = i * i; j <= r; j += i * i) {
            mobi[j] = -10000000000000;
        }
    }
    mobi[1] = 2;
}

ll copnum(ll l1, ll r1, ll l2, ll r2)
{
    ll res = 0;
    ll mx = max(r1, r2);
    for(ll i = 1; i <= mx; ++i) {
        if(mobi[i] <= 0) continue;
        ll v1 = r1 / i - (l1 - 1) / i;
        ll v2 = r2 / i - (l2 - 1) / i;
        if(mobi[i] % 2 == 1) res -= v1 * v2;
        else res += v1 * v2;
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

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    init(max(b, d));
    cout << copnum(a, b, c, d);

    return 0;
}
