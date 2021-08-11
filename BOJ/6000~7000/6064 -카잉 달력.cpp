#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

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

struct CRT
{
    // x = v (mod m)
    struct Con
    {
        ll v, m;
    };

    Con get(Con c1, Con c2)
    {
        if(c1.m < c2.m) swap(c1, c2);
        ENode en = eeuc(c1.m, c2.m);
        if((c1.v - c2.v) % en.g != 0) return { -1, -1 };

        ll c = (c2.v - c1.v) % c2.m;
        if(c < 0) c += c2.m;

        ll resm = c1.m * c2.m / en.g;
        ll resv = en.s * c / en.g * c1.m + c1.v;
        resv %= resm;
        if(resv < 0) resv += resm;
        return { resv, resm };
    }
};

int tNum;
CRT crt;
int n, m, x, y;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> m >> n >> x >> y;
        CRT::Con c1 = { x - 1, m };
        CRT::Con c2 = { y - 1, n };
        auto res = crt.get(c1, c2);
        if(res.m == -1) cout << "-1\n";
        else {
            cout << res.v + 1 << "\n";
        }
    }

    return 0;
}
