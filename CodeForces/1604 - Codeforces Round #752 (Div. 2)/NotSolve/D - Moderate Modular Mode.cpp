#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <numeric>
using namespace std;

using ll = long long int;

int tNum;
ll x, y;

struct ENode
{
    ll s;
    ll t;
    ll g;
};

ENode eeuc(ll a, ll b)
{
    if(b == 0) return { 1, 0, a };

    ll r = a % b;
    auto res = eeuc(b, r);
    ll x = res.t;
    ll y = res.s - a / b * res.t;
    return { x, y, res.g };
}

// Ax+By=C, D=gcd(A, B)=g
// x0 = s * C/D       y0 = t * C/D
// s = x0 + k * B/D   t = y0 - k * A/D

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> x >> y;
        if(x < y) {
            for(ll i = y; i >= x; --i) {
                if((i % x) == (y % i)) {
                    cout << i << "\n";
                    assert((i % x) == (y % i));
                    break;
                }
            }

            continue;
        } else if(x == y) {
            cout << x << "\n";
        } else {
            ll cur = y + 1;
            ll curx = cur % x;
            if(curx < y) {
                cur += y - curx;
            } else if(curx > y) {
                cur += (x - cur) + y;
            }
            cout << cur << "\n";
            //assert((cur % x) == (y % cur));
        }
    }

    return 0;
}
