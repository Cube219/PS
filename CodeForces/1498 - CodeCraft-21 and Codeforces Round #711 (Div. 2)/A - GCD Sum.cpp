#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;


ll gcd(ll a, ll b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

ll n;

ll p(ll v)
{
    ll t1 = 0;
    ll tmp = v;
    while(tmp > 0) {
        t1 += tmp % 10;
        tmp /= 10;
    }
    ll g = gcd(v, t1);
    return g;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < 5; ++i) {
            ll res = p(n);
            if(res > 1) break;
            n++;
        }
        cout << n << "\n";
    }

    return 0;
}
