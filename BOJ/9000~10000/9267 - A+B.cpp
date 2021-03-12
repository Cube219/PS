#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

// MSVS에서는 __int128 지원이 안 되기 때문에 불가능.
// 코딩은 MSVS에서 하기 때문에 임시로 넣어둔 것 (채점은 GCC)
#ifdef _WIN32
using ll = long long int;
#else
using ll = __int128;
#endif

ll n;

struct ENode
{
    ll x;
    ll y;
    ll g;
};
ENode eeuc(ll a, ll b)
{
    if(b == 0) return { 1, 0, a };

    ll r = a % b;
    auto res = eeuc(b, r);
    ll x = res.y;
    ll y = res.x - a / b * res.y;
    return { x, y, res.g };
}

long long inputa, inputb, inputs;
ll a, b, s;

bool special()
{
    if(s == 0) {
        if(a == 0 || b == 0) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        return true;
    } else if(a == 0) {
        if(b == 0) cout << "NO";
        else if(s % b == 0) cout << "YES";
        else cout << "NO";
        return true;
    } else if(b == 0) {
        if(s % a == 0) cout << "YES";
        else cout << "NO";
        return true;
    }
    return false;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> inputa >> inputb >> inputs;
    a = inputa;
    b = inputb;
    s = inputs;
    if(a < b) swap(a, b);

    if(special() == true) return 0;

    auto e = eeuc(a, b);
    if(s % e.g != 0) {
        cout << "NO";
        return 0;
    }
    e.x *= s / e.g;
    e.y *= s / e.g;

    ll dtx = b / e.g;
    ll dty = a / e.g;
    ll kl = ceil((long double)(-e.x) * ((long double)e.g / b));
    ll kr = floor((long double)(e.y) * ((long double)e.g / a));
    e.x += kl * dtx;
    e.y -= kl * dty;
    for(ll k = kl; k <= kr + 1; k++) {
        if(e.x < 0) {
            e.x += dtx;
            e.y -= dty;
            continue;
        }
        if(e.y < 0) break;

        ENode res = eeuc(e.x, e.y);
        if(res.g == 1) {
            cout << "YES";
            return 0;
        }
        e.x += dtx;
        e.y -= dty;
    }

    cout << "NO";

    return 0;
}
