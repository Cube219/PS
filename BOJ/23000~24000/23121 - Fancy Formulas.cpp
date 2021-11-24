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

// (a / b) % mod == (a * b^(mod-2)) % mod
ll divmod(ll a, ll b, ll mod)
{
    ll res = 1;
    ll ex = mod - 2;
    while(ex > 0) {
        if(ex % 2 != 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        ex /= 2;
    }
    res = (res * a) % mod;
    return res;
}

ll p, q;
ll a, b, c, d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> p >> q;
    for(int i = 0; i < q; ++i) {
        cin >> a >> b >> c >> d;
        if((a + b) % p != (c+d) % p) {
            cout << "-1\n";
            continue;
        }
        if(a == c && b == d) {
            cout << "0\n";
            continue;
        }

        int rr = -1;
        for(int j = 1; j < 63; ++j) {
            ll k = 1LL << j;

            ll right = (c - k * a) % p;
            right += p;
            ll left = -(a + b);
            left %= p;
            left += p;
            ll t = divmod(right, left, p);

            if(0 <= t && t < k) {
                rr = j;
                break;
            }
        }
        cout << rr << "\n";
    }

    return 0;
}
