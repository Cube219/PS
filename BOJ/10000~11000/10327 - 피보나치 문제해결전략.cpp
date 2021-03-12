#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

using ll = long long int;

int tNum;
ll n;

struct ENode
{
    ll x;
    ll y;
    ll g;
};
ENode cal(ll a, ll b)
{
    if(b == 0) return { 1, 0, a };

    ll r = a % b;
    auto res = cal(b, r);
    ll x = res.y;
    ll y = res.x - a / b * res.y;
    return { x, y, res.g };
}

ll r1, r2;
vector<ll> f;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    f.push_back(1);
    f.push_back(1);
    int idx = 2;
    while(1) {
        ll t = f[idx - 1] + f[idx - 2];
        f.push_back(t);
        idx++;
        if(t > 1000000000) break;
    }

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {

        cin >> n;
        r1 = 1;
        r2 = n - 1;

        for(int i = 0; i < f.size() - 1; ++i) {
            ll a = f[i];
            ll b = f[i + 1];
            ENode res = cal(a, b);
            ll x = res.x * n;
            ll y = res.y * n;

            ll k = min(ceil(-(double)x / b), floor((double)y / a));
            x += k * b;
            y -= k * a;
            if(x > y || x == 0) {
                ll t = x + y;
                x = y;
                y = t;
            }

            if(x > 0 && y > 0) {
                if(y < r2 || (y == r2 && x < r1)) {
                    r1 = x;
                    r2 = y;
                }
            }
        }

        cout << r1 << " " << r2 << "\n";
    }

    return 0;
}
