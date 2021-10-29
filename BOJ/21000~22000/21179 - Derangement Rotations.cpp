#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;

ll n, p, res;
ll p2[1000001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> p;

    p2[0] = 1;
    for(int i = 1; i <= n; ++i) {
        p2[i] = (p2[i - 1] * 2) % p;
    }

    for(ll i = 2; i < n; ++i) {
        ll g = gcd(n, i);
        ll v = (p2[g - 1] - 1 + p) % p;
        v = (v * (n - 2)) % p;
        res = (res + v) % p;
    }
    cout << res;

    return 0;
}
